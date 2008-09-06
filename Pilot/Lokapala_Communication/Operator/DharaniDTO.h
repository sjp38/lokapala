/**@file	DharaniDTO.h
 * @brief	DharaniDTO를 정의
 * @author	siva
 */

#ifndef DHARANI_DTO_H
#define DHARANI_DTO_H

/**@ingroup GroupDharani
 * @class	CDharaniDTO
 * @brief	외부와 Dharani 컴포넌트 사이의 통신에서 사용되는 데이터 구조.
 *			메세지와 주소로 구성되며, 주소는 사설 ip와 공용 ip(공유기의 ip)로 구성된다.
 */
class CDharaniDTO
{
public :
	char *m_message;
	DWORD m_globalIp;
	DWORD m_localIp;

	CDharaniDTO(){}
	~CDharaniDTO(){}
};

#endif