import hlt.*;
import java.util.PriorityQueue;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import hlt.Ship;


public class MyBot {

	public static void main(final String[] args) {
		final Networking networking = new Networking();
		final GameMap gameMap = networking.initialize("Tamagocchi");

		// We now have 1 full minute to analyse the initial map.
		final String initialMapIntelligence =
				"width: " + gameMap.getWidth() +
				"; height: " + gameMap.getHeight() +
				"; players: " + gameMap.getAllPlayers().size() +
				"; planets: " + gameMap.getAllPlanets().size();
		Log.log(initialMapIntelligence);

		final ArrayList<Move> moveList = new ArrayList<>();



		for (;;){
			moveList.clear();
			networking.updateMap(gameMap);
			//HashMap<Planet,Ship> planned = new HashMap<Planet, Ship>();
			for (final Ship ship : gameMap.getMyPlayer().getShips().values()) {

				PriorityQueue<Planet> closestPlanets = new PriorityQueue<Planet>(
						new Comparator() {
							@Override
							public int compare(Object a, Object b) {
								Planet o1 = (Planet)a;
								Planet o2 = (Planet)b;
								if(o1.getDistanceTo(ship) > o2.getDistanceTo(ship)) {
									return 1;
								} else if (o1.getDistanceTo(ship) == o2.getDistanceTo(ship)) {
									return 0;
								} else {
									return -1;
								} 
							}
						});

				if (ship.getDockingStatus() != Ship.DockingStatus.Undocked) {
					continue;
				}

				for (final Planet planet : gameMap.getAllPlanets().values()) {
					closestPlanets.add(planet);
				}
				while(!closestPlanets.isEmpty()){    
					Planet planet = closestPlanets.poll();


					Planet tmp = planet;
					while (tmp.isOwned() && closestPlanets.size() != 0) {
						tmp = closestPlanets.poll();
					}

					if (closestPlanets.size() != 0) {
						planet = tmp;
					}

					if (ship.canDock(planet)) {
						moveList.add(new DockMove(ship, planet));
						break;
					}


					final ThrustMove newThrustMove = Navigation.navigateShipToDock(gameMap, ship, planet, Constants.MAX_SPEED);
					if (newThrustMove != null) {
						moveList.add(newThrustMove);
					}
					break;
				}
			}
			Networking.sendMoves(moveList);
		}
	}
}
