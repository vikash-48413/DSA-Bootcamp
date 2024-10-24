import networkx as nx
import matplotlib.pyplot as plt
import heapq
from datetime import datetime
from typing import Dict, List, Tuple, Any

def create_indian_cities_graph():
    """Create a graph of major Indian cities with actual distances and additional metadata"""
    graph = {
        'Delhi': {
            'Mumbai': {'distance': 1414, 'route': 'NH48', 'traffic': 'moderate'},
            'Kolkata': {'distance': 1474, 'route': 'NH19', 'traffic': 'heavy'},
            'Jaipur': {'distance': 281, 'route': 'NH48', 'traffic': 'low'},
            'Lucknow': {'distance': 555, 'route': 'NH27', 'traffic': 'moderate'},
            'Ahmedabad': {'distance': 934, 'route': 'NH48', 'traffic': 'moderate'}
        },
        'Mumbai': {
            'Bangalore': {'distance': 984, 'route': 'NH48', 'traffic': 'moderate'},
            'Hyderabad': {'distance': 706, 'route': 'NH65', 'traffic': 'heavy'},
            'Ahmedabad': {'distance': 524, 'route': 'NH48', 'traffic': 'low'},
            'Jaipur': {'distance': 1148, 'route': 'NH48', 'traffic': 'moderate'}
        },
        'Kolkata': {
            'Hyderabad': {'distance': 1515, 'route': 'NH16', 'traffic': 'heavy'},
            'Chennai': {'distance': 1679, 'route': 'NH16', 'traffic': 'moderate'},
            'Lucknow': {'distance': 985, 'route': 'NH27', 'traffic': 'low'}
        },
        'Bangalore': {
            'Chennai': {'distance': 346, 'route': 'NH48', 'traffic': 'moderate'},
            'Hyderabad': {'distance': 574, 'route': 'NH44', 'traffic': 'heavy'},
            'Mumbai': {'distance': 984, 'route': 'NH48', 'traffic': 'moderate'}
        },
        'Chennai': {
            'Hyderabad': {'distance': 627, 'route': 'NH65', 'traffic': 'moderate'},
            'Bangalore': {'distance': 346, 'route': 'NH48', 'traffic': 'low'},
            'Kolkata': {'distance': 1679, 'route': 'NH16', 'traffic': 'heavy'}
        },
        'Hyderabad': {
            'Mumbai': {'distance': 706, 'route': 'NH65', 'traffic': 'moderate'},
            'Bangalore': {'distance': 574, 'route': 'NH44', 'traffic': 'heavy'},
            'Chennai': {'distance': 627, 'route': 'NH65', 'traffic': 'moderate'},
            'Kolkata': {'distance': 1515, 'route': 'NH16', 'traffic': 'heavy'}
        },
        'Ahmedabad': {
            'Mumbai': {'distance': 524, 'route': 'NH48', 'traffic': 'moderate'},
            'Jaipur': {'distance': 657, 'route': 'NH48', 'traffic': 'low'},
            'Delhi': {'distance': 934, 'route': 'NH48', 'traffic': 'heavy'}
        },
        'Jaipur': {
            'Delhi': {'distance': 281, 'route': 'NH48', 'traffic': 'low'},
            'Ahmedabad': {'distance': 657, 'route': 'NH48', 'traffic': 'moderate'},
            'Lucknow': {'distance': 574, 'route': 'NH27', 'traffic': 'moderate'}
        },
        'Lucknow': {
            'Delhi': {'distance': 555, 'route': 'NH27', 'traffic': 'moderate'},
            'Kolkata': {'distance': 985, 'route': 'NH27', 'traffic': 'heavy'},
            'Jaipur': {'distance': 574, 'route': 'NH27', 'traffic': 'low'}
        }
    }
    return graph

def dijkstra(graph: Dict[str, Dict[str, Dict[str, Any]]], start: str, end: str) -> Tuple[List[str], float]:
    """
    Implements Dijkstra's algorithm to find the shortest path between two cities.
    
    Args:
        graph: The graph representation of cities and their connections
        start: Starting city
        end: Destination city
    
    Returns:
        Tuple containing the path (list of cities) and total distance
    """
    # Initialize distances to infinity for all nodes except start
    distances = {city: float('infinity') for city in graph}
    distances[start] = 0
    
    # Keep track of previous nodes to reconstruct path
    previous = {city: None for city in graph}
    
    # Priority queue to store (distance, city) pairs
    # Using distance as priority ensures we always process closest unvisited node
    pq = [(0, start)]
    
    # Keep track of processed nodes
    processed = set()
    
    while pq:
        # Get the unprocessed node with smallest distance
        current_distance, current_city = heapq.heappop(pq)
        
        # If we've reached our destination, we're done
        if current_city == end:
            break
            
        # Skip if we've already processed this city
        if current_city in processed:
            continue
            
        # Mark as processed
        processed.add(current_city)
        
        # Check all neighboring cities
        for neighbor, data in graph[current_city].items():
            # Skip processed neighbors
            if neighbor in processed:
                continue
                
            # Calculate new distance to neighbor
            new_distance = current_distance + data['distance']
            
            # If we found a shorter path, update it
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
                previous[neighbor] = current_city
                heapq.heappush(pq, (new_distance, neighbor))
    
    # Reconstruct the path
    path = []
    current_city = end
    
    while current_city is not None:
        path.append(current_city)
        current_city = previous[current_city]
    
    # Reverse path to get start→end order
    path.reverse()
    
    # Return path and total distance
    return path, distances[end]

def calculate_eta(distance: float, traffic: str) -> float:
    """Calculate estimated time of arrival based on distance and traffic"""
    average_speed = {
        'low': 70,
        'moderate': 55,
        'heavy': 40
    }
    speed = average_speed[traffic]
    return distance / speed

def format_route_details(path: List[str], graph: Dict[str, Dict[str, Dict[str, Any]]]) -> str:
    """Format detailed route information including distance, time, and traffic conditions"""
    if not path or len(path) < 2:
        return "No valid route found!"
    
    total_distance = 0
    total_time = 0
    
    details = "\nRoute Details:\n" + "="*70 + "\n"
    details += f"From: {path[0]} → To: {path[-1]}\n\n"
    
    details += f"{'Segment':^30} {'Distance':^10} {'Route':^10} {'Traffic':^10} {'ETA':^10}\n"
    details += "-"*70 + "\n"
    
    # Calculate segment details
    for i in range(len(path)-1):
        start, end = path[i], path[i+1]
        data = graph[start][end]
        distance = data['distance']
        eta = calculate_eta(distance, data['traffic'])
        
        details += f"{f'{start} → {end}':30} {f'{distance}km':10} {data['route']:10} "
        details += f"{data['traffic']:10} {f'{eta:.1f}h':10}\n"
        
        total_distance += distance
        total_time += eta
    
    details += "="*70 + "\n"
    details += f"Total Distance: {total_distance} km\n"
    details += f"Total Travel Time: {total_time:.1f} hours\n"
    current_time = datetime.now()
    arrival_time = current_time.replace(hour=(current_time.hour + int(total_time)) % 24)
    details += f"Expected Arrival: {arrival_time.strftime('%I:%M %p')}\n"
    
    return details

def visualize_route(graph: Dict[str, Dict[str, Dict[str, Any]]], path: List[str] = None) -> None:
    """Visualize the route with improved clarity and information"""
    plt.figure(figsize=(15, 12))
    G = nx.Graph()
    
    # Add edges to graph
    for city1, connections in graph.items():
        for city2, data in connections.items():
            G.add_edge(city1, city2, **data)
    
    # Get positions for cities
    pos = get_city_positions()
    
    # Draw base graph
    nx.draw_networkx_nodes(G, pos, node_color='lightgray', node_size=2000)
    
    # Draw edges with traffic-based colors
    traffic_colors = {'low': 'green', 'moderate': 'orange', 'heavy': 'red'}
    for (city1, city2, data) in G.edges(data=True):
        nx.draw_networkx_edges(G, pos, 
                             edgelist=[(city1, city2)],
                             edge_color=traffic_colors[data['traffic']],
                             width=1,
                             alpha=0.3)
    
    # Highlight selected route
    if path and len(path) > 1:
        path_edges = list(zip(path[:-1], path[1:]))
        nx.draw_networkx_edges(G, pos, 
                             edgelist=path_edges,
                             edge_color='blue',
                             width=3)
        
        # Highlight start and end points
        nx.draw_networkx_nodes(G, pos,
                             nodelist=[path[0]],
                             node_color='lime',
                             node_size=2500)
        nx.draw_networkx_nodes(G, pos,
                             nodelist=[path[-1]],
                             node_color='red',
                             node_size=2500)
    
    # Add labels
    nx.draw_networkx_labels(G, pos, font_size=10, font_weight='bold')
    
    # Add edge labels with distances
    edge_labels = {(city1, city2): f"{data['distance']}km\n{data['route']}"
                  for (city1, city2, data) in G.edges(data=True)}
    nx.draw_networkx_edge_labels(G, pos, edge_labels, font_size=8)
    
    plt.title("Indian Cities Route Map" + 
             ("\n" + " → ".join(path) if path else ""), 
             pad=20)
    plt.axis('off')
    plt.tight_layout()
    plt.show()

def get_city_positions():
    """Get geographical positions for cities"""
    return {
        'Delhi': (6.5, 8.5),
        'Mumbai': (2, 4.2),
        'Kolkata': (9.2, 5),
        'Bangalore': (4, 1),
        'Chennai': (6.2, 1),
        'Hyderabad': (5, 3.2),
        'Ahmedabad': (1, 6.2),
        'Jaipur': (4, 7.2),
        'Lucknow': (7.2, 6.8)
    }

def main():
    """Main function to run the routing system"""
    graph = create_indian_cities_graph()
    
    print("\nIndian Cities Route Finder")
    print("="*50)
    print("\nAvailable Cities:")
    for i, city in enumerate(sorted(graph.keys()), 1):
        print(f"{i}. {city}")
    
    while True:
        print("\n" + "="*50)
        start = input("\nEnter starting city (or 'quit' to exit): ").title()
        if start.lower() == 'quit':
            break
            
        if start not in graph:
            print(f"Error: '{start}' is not a valid city!")
            continue
            
        end = input("Enter destination city: ").title()
        if end not in graph:
            print(f"Error: '{end}' is not a valid city!")
            continue
            
        if start == end:
            print("Start and destination cities are the same!")
            continue
        
        # Find shortest path
        path, total_distance = dijkstra(graph, start, end)
        
        # Display route details
        print(format_route_details(path, graph))
        
        # Visualize route
        visualize_route(graph, path)
        
        choice = input("\nPlan another route? (yes/no): ").lower()
        if choice != 'yes':
            break
    
    plt.close('all')

if __name__ == "__main__":
    main()