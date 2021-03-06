#include "thread_functions.h"
#include "timing.h"

void sendingThread(zmq::context_t* p_zmqcontext){
    std::string status = "Sendin Thread: init";
    double t_now = clock();	
	int val = 6; //buffer size

    printf("%s connecting to %s\n", status.c_str(), cfg_ros_master.c_str());
	
	zmq::socket_t socket_in(*p_zmqcontext, ZMQ_PULL);    
	socket_in.setsockopt(ZMQ_RCVHWM, &val, sizeof(val));  //prevent buffer get overfilled
	socket_in.setsockopt(ZMQ_SNDHWM, &val, sizeof(val));  //prevent buffer get overfilled
	socket_in.bind(zmq_compressed);

	zmq::socket_t socket_out(*p_zmqcontext, ZMQ_PUB);
    socket_out.setsockopt(ZMQ_RCVHWM, &val, sizeof(val));  //prevent buffer get overfilled
	socket_out.setsockopt(ZMQ_SNDHWM, &val, sizeof(val));  //prevent buffer get overfilled
	socket_out.connect(cfg_ros_master.c_str());
    _TIME
    
    int more;
    size_t more_size = sizeof (more);
	
    while(true){
        status = "SendingThread: Recived message";
		zmq::message_t in1;
        socket_in.recv(&in1);
        socket_in.getsockopt(ZMQ_RCVMORE, &more, &more_size);
#ifdef _DEBUG
        std::cout << "SendingThread: Recieved message with size:" << in1.size() << std::endl;
#endif
        _TIME
        status = "SendingThread: Send message";
        socket_out.send(in1, more? ZMQ_SNDMORE: 0);  
        _TIME
	}
}