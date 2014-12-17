#ifndef _EntityVector_included_
#define _EntityVector_included_

#include <vector>
#include <functional>
#include "Tools.h"
template<class T>
class EntityVector
{
public:
	void constructVector(std::vector<XMLSerializable*> & vVector)
	{
		for (auto pObject : vVector)
		{
			T * pEntity = dynamic_cast<T*>(pObject);

			if (pEntity != NULL)
			{
				m_vEntity.push_back(pEntity);
			}
		}
	}

	T * generate(std::function<bool(T*)> pFunc)
	{
		std::vector<T*> vTemp;

		for (auto pEntity : m_vEntity)
		{
			if (pFunc(pEntity))
			{
				vTemp.push_back(pEntity);
			}
		}

		if (vTemp.size() == 0)
			return NULL;

		return new T(*vTemp[Tools::randomValue(vTemp.size())]);

	}

private:
	std::vector<T*> m_vEntity;
};


#endif



