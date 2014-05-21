%module qitkat

class quantum_manager_server {
public:
	quantum_manager_server(unsigned short listenport);
	void listen();
};
