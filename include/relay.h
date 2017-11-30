#ifndef RELAY_H
#define RELAY_H

#ifndef BOOL_TYPEDEF
#define bool    _Bool
#define true    1
#define false   0
#endif

void initRelay();
void setRelay (bool on);
void refreshRelay();

#endif