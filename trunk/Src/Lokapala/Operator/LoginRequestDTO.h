/**@file	LoginRequestDTO.h
 * @brief	�α��� ��û ������ ��� CLoginRequestDTO Ŭ������ �����Ѵ�.
 * @author	siva
 */

#ifndef LOGIN_REQUEST_DTO_H
#define LOGIN_REQUEST_DTO_H

/**@ingroup	GroupCCM
 * @class	CLoginRequestDTO
 * @brief	�α��� ��û �� ���Ǵ� ������ ��´�. UserDataDTO���� �ٷ�� �����Ϳ� �α��� ��û ���� ���� �ּ� ������ ���Եȴ�.\n
 *			m_level�� DCM���� �α��� ��û ��� ���� ó���� ��Ź�� �� -1�� ������ �ʱ�ȭ �Ǹ�, DCM�� �α��� ��� �޼����� ������� �� �� ���� ���� ���� ����.
 */
class CLoginRequestDTO
{
public :
	CString m_globalIp;
	CString m_localIp;
	CString m_name;
	CString m_lowLevelPassword;
	CString m_highLevelPassword;
	int m_level;

	CLoginRequestDTO(){}
	~CLoginRequestDTO(){}
};


#endif