all:test_server.cpp server.cpp server.h test_client.cpp client.cpp client.h global.h
	g++ -o test_client test_client.cpp client.cpp -lpthread -ljsoncpp -lmysqlclient
	g++ -o test_server test_server.cpp server.cpp -lpthread -lmysqlclient -ljsoncpp 
test_server:test_server.cpp server.cpp server.h global.h
	g++ -o test_server test_server.cpp server.cpp -lpthread -lmysqlclient -ljsoncpp 
test_client:test_client.cpp client.cpp client.h global.h
	g++ -o test_client test_client.cpp client.cpp -lpthread -ljsoncpp -lmysqlclient
clean:
	rm test_server
	rm test_client