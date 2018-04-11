all:
	g++ -std=c++11 server/*.cpp -lpthread -o vending_sys
	g++ -std=c++11 client/*.cpp -o kiosk

clean:
	rm vending_sys kiosk
