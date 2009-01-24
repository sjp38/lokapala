/**@file	NeverDieBI.h
 * @brief	NDM�� BI ����.
 * @author	siva
 */

#ifndef NEVERDIE_BI_H
#define NEVERDIE_BI_H

/**@ingroup	GroupNDM
 * @class	CNeverDieBI
 * @brief	NeverDie Manager �� Button Interface.
 * @remarks	�������̴�.
 */
class CNeverDieBI
{
public :
	/**@brief	���� ���� �ʰ� �Ѵ�.
	 */
	virtual void StartNeverDie() = 0;
	/**@brief	���� ���� �ְ� �Ѵ�.
	 */
	virtual void StopNeverDie() = 0;

	/**@brief	���� �� �ִ��� �׾ �ȵǴ��� �˷��ش�.
	 * @return	�׾ �ȵȴٸ� true, �׾ �ȴٸ� false
	 */
	virtual bool GetNeverDieState() = 0;
};

#endif