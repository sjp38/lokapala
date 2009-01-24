/**@file	UserDTO.h
 * @brief	CUserDTO Ŭ������ �����Ѵ�.
 * @author	siva
 */

#ifndef USER_DTO_H
#define USER_DTO_H

/**@ingroup	GroupDAM
 * @class	CUserDTO
 * @brief	����� ���� ������ ���´�. ���� ����� ������ �����ϴµ��� ���Ǹ�, �α��� ��û�����ε� ���ȴ�.
 */
class CUserDTO
{
public :
	CString m_name;
	CString m_lowLevelPassword;
	CString m_highLevelPassword;
	int m_level;

	CUserDTO(CString a_name, CString a_lowLevelPassword, CString a_highLevelPassword);
	CUserDTO(CString a_name, CString a_lowLevelPassword, CString a_highLevelPassword, int a_level);
	CUserDTO(){}
	~CUserDTO(){}

private :
	CString HashMessage(CString a_message);
};


#endif