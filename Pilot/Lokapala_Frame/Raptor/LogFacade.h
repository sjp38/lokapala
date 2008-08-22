/**@file	LogFacade.h
 * @brief	Log Manager�� Facade ����.
 * author	siva
 */

#ifndef LOG_FACADE_H
#define LOG_FACADE_H

#include "LogBI.h"

/**@ingroup GroupLGM
 * @class	CLogFacade
 * @brief	LGM�� Facade.
 * @remarks	SingleTon�� ����Ѵ�.
 */
class CLogFacade : public CLogBI
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
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
	/**@brief	������	*/
	CLogFacade(){}
	/**@brief	�Ҹ���	*/
	~CLogFacade(){}
private :
	/**@brief	singleton	*/
	static CLogFacade *m_instance;
};

#endif