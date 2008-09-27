/**@file	StateDataDTO.h
 * @brief	���¿� ���� �����͸� �����ϴ� DTO�� �����Ѵ�.
 * @author	siva
 */

#ifndef STATE_DATA_DTO_H
#define STATE_DATA_DTO_H

enum State {HW, SW, Fixed, Verified};

/**@ingroup	GroupDAM
 * @class	CStateDataDTO
 * @brief	���¿� ���� ������ �����Ѵ�.
 */
class CStateDataDTO
{
	int m_stateId;
	CString m_globalIp;
	CString m_localIp;
	enum State m_state;
	CString m_comment;
	CString m_date;
};

#endif