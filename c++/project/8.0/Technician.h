#ifndef __TECHNICION_H_
#define __TECHNICION_H_

#include "Employee.h"

class Technician:virtual public Employee{
public:
    Technician(const string& name,double salary,double allow);
    void printExtra(void)const;
    double calMerit(void);
protected:
    double m_allow;//研发津贴
};

#endif//__TECHNICION_H_


