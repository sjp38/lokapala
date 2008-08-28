/**@file	DharaniExternSD.h
 * @brief	Dharani ������Ʈ�κ��� �ܺη��� SD�� ����.
 * @author	siva
 */

#ifndef DHARANI_EXTERN_SD_H
#define DHARANI_EXTERN_SD_H

/**@ingroup	GroupDharani
 * @class	CDharaniExternSD
 * @brief	Dharani ������Ʈ�κ��� �ܺη��� SD. Dharani ������Ʈ�� ����ϴ� Ŭ���̾�Ʈ ������ �ϼ��ؾ� �Ѵ�.\n
 *			Dharani���� Ŭ���̾�Ʈ �������� ��� �������� ���ȴ�. ��ü�����δ� Read�� ������ �˸� �� ���ȴ�.
 */
class CDharaniExternSD
{
public :
	void NotifyReceived(CString a_srcAddress, CString a_message);
};


#endif