#include "item.h"

void Item::drop(int posx,int posy) {
	x = posx;
	y = posy;
	owned = false;
}

bool Item::checkName(std::string n){
	if (name == n){
		return true;
	}
	else {
		for (int i = 0;i<alternatives.size();i++){
			if (n == alternatives[i]){
				return true;
			}
		}
	}
	return false;

}