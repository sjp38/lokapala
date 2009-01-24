/**@file	LogFacade.h
 * @brief	Log Manager의 Facade 정의.
 * author	siva
 */

#ifndef LOG_FACADE_H
#define LOG_FACADE_H

#include "LogBI.h"

/**@ingroup GroupLGM
 * @class	CLogFacade
 * @brief	LGM의 Facade.
 * @remarks	SingleTon을 사용한다.
 */
class CLogFacade : public CLogBI
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
	 */
	static CLogFacade *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CLogFacade();
		}
		return m_instance;
	}
protected :
	/**@brief	생성자	*/
	CLogFacade(){}
	/**@brief	소멸자	*/
	~CLogFacade(){}
private :
	/**@brief	singleton	*/
	static CLogFacade *m_instance;
};

#endif