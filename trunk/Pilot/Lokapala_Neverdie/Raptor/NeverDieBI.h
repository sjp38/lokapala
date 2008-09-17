/**@file	NeverDieBI.h
 * @brief	NDM의 BI 정의.
 * @author	siva
 */

#ifndef NEVERDIE_BI_H
#define NEVERDIE_BI_H

/**@ingroup	GroupNDM
 * @class	CNeverDieBI
 * @brief	NeverDie Manager 의 Button Interface.
 * @remarks	인터페이다.
 */
class CNeverDieBI
{
public :
	/**@brief	절대 죽지 않게 한다.
	 */
	virtual void StartNeverDie() = 0;
	/**@brief	죽을 수도 있게 한다.
	 */
	virtual void StopNeverDie() = 0;
};

#endif