#include "switch.h"

void Switch::openSwitch(ESWITCH e){
	unsigned int i = e / SWITCH_SIZE;
	unsigned int j = e % SWITCH_SIZE;
	if(m_switchs.size() <= i){
		UINT8 u = 00;
		do {
			m_switchs.push_back(u);
		}while(m_switchs.size() <= i);
	}
	m_switchs[i] |= BTRUE << j;
}

void Switch::openSwitch(ESWITCH e, size_t size){
	for(int i = 0; i<size; ++i){
		openSwitch(ESWITCH(e + i));
	}
}

void Switch::setSwitch(ESWITCH e, UINT8 val, size_t size){
	for(int i = 0; i<size; ++i){
		if(val & BTRUE)
			openSwitch(ESWITCH(e + i));
		else 
			closeSwitch(ESWITCH(e + i));
		val >> 1;
	}
}

void Switch::closeSwitch(ESWITCH e){
	unsigned int i = e / SWITCH_SIZE;
	unsigned int j = e % SWITCH_SIZE;
	if(m_switchs.size() <= i){
		return;
	}else{
		m_switchs[i] &= ~(BTRUE << j);
	}
}

bool Switch::stateSwitch(ESWITCH e){
	unsigned int i = e / SWITCH_SIZE;
	unsigned int j = e % SWITCH_SIZE;
	if((m_switchs.size() > i) && (m_switchs[i] & (BTRUE << j)))
		return true;
	return false;
}

std::string Switch::packSwitch(){
	std::string str = "";
	for(auto c : m_switchs){
		str += c;
	}
	return str;
}

void Switch::unpackSwitch(std::string switchs){
	size_t size = switchs.size();
	m_switchs.clear();
	if(size > 0){
		UINT8 u;
		for(auto c : switchs){
			u = c;
			m_switchs.push_back(u);
		}
	}
}

int main(){
	Switch gs;
	gs.openSwitch(eswitch1);
	gs.openSwitch(eswitch2);
	gs.openSwitch(eswitch3);
	gs.closeSwitch(eswitch2);
	gs.closeSwitch(eswitch4);
	bool b = gs.stateSwitch(eswitch1);
	std::string str = gs.packSwitch();
	gs.unpackSwitch(str);

	return 0;
}