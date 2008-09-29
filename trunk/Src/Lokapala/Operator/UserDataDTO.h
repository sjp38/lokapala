/**@file	UserDataDTO.h
 * @brief	���� ������ ������ ��� DTO�� �����Ѵ�.
 * @author	siva
 */

#ifndef USER_DATA_DTO_H
#define USER_DATA_DTO_H

/**@ingroup	GroupDAM
 * @class	CUserDataDTO
 * @brief	���� ������ ������ ��´�.\n
 * @remarks	��й�ȣ�� ��� �ܹ��� �ؽ��� ��ģ ������ ���´�.\n
 *			���� id�� ����� �ؽ� ���� �ο췹�� �н�����(�й�)��.
 */
class CUserDataDTO
{
public :
	/**@brief	���⼱ �ܼ��� �ش� ������ low level password�� ����Ѵ�.	*/
	CString m_userId;
	CString m_name;
	CString m_lowLevelPassword;
	/**@brief	sha1���� �ؽ̵� digest message�� ���´�.	*/
	CString m_highLevelPassword;
	int m_level;
	/**@brief	���ӵ� ������� TRUE, �ƴϸ� FALSE	*/
	BOOL m_connected;
	/**@brief	���ӵǾ� �ִٸ�, ������ �ڸ��� id	*/
	CString m_seatId;
	
	CUserDataDTO(CString a_userId, CString a_name, CString a_lowLevelPassword, CString a_highLevelPassword, int level=0);
	CUserDataDTO(){}
	~CUserDataDTO(){}

private :
	CString HashMessage(CString a_message);
};


#endif