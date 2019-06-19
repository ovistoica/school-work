#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>

#include "stdio.h"
#include "string.h"

int main()
{
    BIO * bio;
    SSL * ssl;
    SSL_CTX * ctx;

    int p;

    char * request = "GET / HTTP/1.1\r\nHost: www.verisign.com\r\n\r\n";
    char r[1024];

    /* initializare librarie */

    SSL_library_init ();
    ERR_load_BIO_strings();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    /* TODO initializare context */
    ctx = SSL_CTX_new(SSLv23_client_method());


    /* incarca trust store */


    if(! SSL_CTX_load_verify_locations(ctx, "TrustStore.pem", NULL))
    {
        fprintf(stderr, "Error loading trust store\n");
        ERR_print_errors_fp(stderr);
        SSL_CTX_free(ctx);
        return 0;
    }


    /* stabileste conexiune */

    bio = BIO_new_ssl_connect(ctx);

    /* Seteaza flag SSL_MODE_AUTO_RETRY  */

    BIO_get_ssl(bio, & ssl);
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

    /* TODO setup conexiune */
    bio = BIO_new_connect("www.verisign.com:443");
    if(BIO_do_connect(bio) <= 0){
        fprintf(stderr, "Error connecting bio\n");
        return -1;
    }

    /* TODO verifica certificat */
    if(SSL_get_verify_result(ssl) != X509_V_OK)
    {
      fprintf(stderr, "Error verifying certificate\n");
      BIO_free_all(bio);
      SSL_CTX_free(ctx);
      return -1;
    }


    /* Trimite request */

    int x = BIO_write(bio, request, strlen(request));
    printf("%d\n", x);

    /* TODO Citeste raspuns si pregateste  output*/
my_bio_read:
    p = BIO_read(bio, r, sizeof(r));
    ERR_print_errors_fp(stderr);
    printf("P:%d\n", p);
    if(p == 0){
      fprintf(stderr, "Error closed connexion from server\n");
      BIO_free_all(bio);
      SSL_CTX_free(ctx);
      return -1;
    } else if(r < 0){
      if(!BIO_should_retry(bio)) {
        fprintf(stderr, "Error failed reading\n");
        BIO_free_all(bio);
        SSL_CTX_free(ctx);
        return -1;
      }
      goto my_bio_read;
    }

    printf("%s\n", r);


    /* Inchide conexiune si elibereaza context */

    BIO_free_all(bio);
    SSL_CTX_free(ctx);
    return 0;
}
