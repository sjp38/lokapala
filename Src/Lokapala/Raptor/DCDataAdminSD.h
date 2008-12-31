/**@file	DCDataAdminSD.h
 * @brief	DCM���� DAM������ Service Delegate ����.
 * @author	siva
 */

#ifndef DCDATA_ADMIN_SD_H
#define DCDATA_ADMIN_SD_H

/**@ingroup GroupDCM
 * @class	CDCDataAdminSD
 * @brief	DCM���� DAM������ Service Delegate. DCM���� DAM���� �䱸�ϴ� �ٰ� ���� �� ���ȴ�.
 * @remarks	singleton�� ����Ѵ�.
 */
class CDCDataAdminSD
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
	 */
	static CDCDataAdminSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDCDataAdminSD();
		}
		return m_instance;
	}

	void RegistUser(void *a_userInfo);
	void RegistUserLevel(int a_level);

	void SaveStatusReportsToFile( CString a_fileName=_T("stateReports.cfg") );
	
protected :
	/**@brief	������	*/
	CDCDataAdminSD(){}
	/**@brief	�Ҹ���	*/
	~CDCDataAdminSD(){}
private :
	/**@brief	singleton.	*/
	static CDCDataAdminSD *m_instance;
};

#endif