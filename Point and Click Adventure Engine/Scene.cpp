#include "Scene.hpp"


bool pc::Scene::sort(const ListObject & l, const ListObject & r) {
	if (l.first < r.first)
		return true;
	return false;
}
