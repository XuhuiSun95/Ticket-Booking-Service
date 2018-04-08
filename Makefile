all:
	g++ -std=c++11 servers/includes/*.cpp servers/movie_server/*.cpp -o movie_server -I servers/includes
	g++ -std=c++11 servers/play_server/*.cpp -o play_server
	g++ -std=c++11 client/*.cpp -o kiosk

clean:
	rm movie_server play_server kiosk
