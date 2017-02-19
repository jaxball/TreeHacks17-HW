#ifndef AMAZONIOTCLIENT_H_
#define AMAZONIOTCLIENT_H_

#include "AWSClient4.h"

class AmazonIOTClient : public AWSClient4 {
  
public:
    AmazonIOTClient();
    char* update_shadow(MinimalString shadow, ActionError& actionError);
    char* get_shadow(ActionError& actionError);
};

#endif /* AMAZONIOTCLIENT_H_ */
