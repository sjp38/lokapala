/**@file	DharaniDTO.h
 * @brief	DharaniDTO�� ����
 * @author	siva
 */

#ifndef DHARANI_DTO_H
#define DHARANI_DTO_H

/**@ingroup GroupDharani
 * @class	CDharaniDTO
 * @brief	�ܺο� Dharani ������Ʈ ������ ��ſ��� ���Ǵ� ������ ����.
 *			�޼����� �ּҷ� �����Ǹ�, �ּҴ� �缳 ip�� ���� ip(�������� ip)�� �����ȴ�.
 */
class CDharaniDTO
{
public :
	char *m_message;
	char *m_publicIp;
	char *m_privateIp;
};

#endif