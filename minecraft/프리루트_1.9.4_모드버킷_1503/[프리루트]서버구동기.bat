@echo off
title ����ũ����Ʈ 1.9.4 ������ ����Ŷ with ������Ʈ
:main
cls
echo.
echo �Ȧ�����������������������������������������������������������
echo ��
echo ��     ������Ʈ�� ����ũ����Ʈ 1.9.4 ������ ����Ŷ
echo ��
echo ��
echo ��   1. ���� ����� (�ڵ� �ڹ� Ž��)
echo ��
echo ��   2. ��弭�� ���� ���
echo ��
echo ��   3. �۾����� �����ϱ�
echo ��
echo ��   4. ������Ʈ ��α� ����
echo ��
echo ��   5. ����
echo ��
echo ��
echo ��  * �ٽ����� ���� : SpongePowered / ���������� ���� : ������Ʈ
echo ��  * �ٽ����� ���� : 5.0.0 ��Ÿ 1503
echo ��  * ž��� ���� ���� : 12.17.0.1968
echo ��  * ���۳�¥ : 2017.04.13
echo ��
echo �Ʀ�����������������������������������������������������������


set /p a=���ϴ� �׸��� ���ڸ� �Է��ϰ� ����(Enter) :
if %a%==1 goto RAM
if %a%==2 goto way
if %a%==3 goto color
if %a%==4 goto blog
if %a%==5 goto exit


:RAM
cls
echo.
echo �Ȧ�������������������������������������������������������������
echo ��
echo ��    ������ ���µ� ����ϰ��� �Ͻô� �� �뷮�� �������ּ���
echo ��
echo ��
echo ��    1. �� 512MB (����� ��ǻ��)
echo ��
echo ��    2. �� 1GB (�Ϲ�)
echo ��
echo ��    3. �� 2GB
echo ��
echo ��    4. �� 4GB
echo ��
echo ��    5. �� 8GB
echo ��
echo ��    6. �� 16GB
echo ��
echo ��
echo ��  * ���ǻ��� 1 : �� 2GB �̻� ����, ��ǻ�Ϳ� �ݵ�� �ڹ� 64��Ʈ
echo ��                 ����"��" ��ġ�Ǿ� �־�� �մϴ� (��ġ:�Ʒ��� 7 �Է�)
echo ��
echo ��  * ���ǻ��� 2 : ��ǻ�Ϳ� �����Ǿ��ִ� ������ 2~3GB ���� �뷮��
echo ��                 ���� �����ؼ� ������ ����ϼž� �մϴ�
echo ��
echo �Ʀ�������������������������������������������������������������


set /p b=���ϴ� �� �뷮 �׸��� ���ڸ� �Է��ϰ� ����(Enter) :
if %b%==1 goto RAM_512
if %b%==2 goto RAM_1
if %b%==3 goto RAM_2
if %b%==4 goto RAM_4
if %b%==5 goto RAM_8
if %b%==6 goto RAM_16
if %b%==7 goto JAVA64


:RAM_512
cls
echo.
echo �Ȧ�������������������������������������������������������������
echo ��
echo ��
echo ��   ������Ʈ�� ����ũ����Ʈ ���������� �̿����ּż� �����Դ�.
echo ��
echo ��
echo ��   ������Ʈ�� �����Ⱑ ������ �̿��� �ڹٸ� �ڵ�����
echo ��      Ž���ϰ� �ֽ��ϴ�. ��ø� ��ٷ��ּ��� :D
echo ��
echo ��
echo ��  * ������� : ���� ������ �����Ͻ� �� stop ��ɾ ġ�ø�
echo ��                    ������ ���������� ����Ǵ� �������ּ���~
echo ��
echo ��
echo �Ʀ�������������������������������������������������������������

java -Xms512M -Xmx512M -jar [Forge]1.9.4_12.17.0.1968.jar
PAUSE
goto main


:RAM_1
cls
echo.
echo �Ȧ�������������������������������������������������������������
echo ��
echo ��
echo ��   ������Ʈ�� ����ũ����Ʈ ���������� �̿����ּż� �����Դ�.
echo ��
echo ��
echo ��   ������Ʈ�� �����Ⱑ ������ �̿��� �ڹٸ� �ڵ�����
echo ��      Ž���ϰ� �ֽ��ϴ�. ��ø� ��ٷ��ּ��� :D
echo ��
echo ��
echo ��  * ������� : ���� ������ �����Ͻ� �� stop ��ɾ ġ�ø�
echo ��                    ������ ���������� ����Ǵ� �������ּ���~
echo ��
echo ��
echo �Ʀ�������������������������������������������������������������

java -Xms1G -Xmx1G -jar [Forge]1.9.4_12.17.0.1968.jar
PAUSE
goto main


:RAM_2
cls
echo.
echo �Ȧ�������������������������������������������������������������
echo ��
echo ��
echo ��   ������Ʈ�� ����ũ����Ʈ ���������� �̿����ּż� �����Դ�.
echo ��
echo ��
echo ��   ������Ʈ�� �����Ⱑ ������ �̿��� �ڹٸ� �ڵ�����
echo ��      Ž���ϰ� �ֽ��ϴ�. ��ø� ��ٷ��ּ��� :D
echo ��
echo ��
echo ��  * ������� : ���� ������ �����Ͻ� �� stop ��ɾ ġ�ø�
echo ��                    ������ ���������� ����Ǵ� �������ּ���~
echo ��
echo ��
echo �Ʀ�������������������������������������������������������������

java -Xms1G -Xmx2G -jar [Forge]1.9.4_12.17.0.1968.jar
PAUSE
goto main


:RAM_4
cls
echo.
echo �Ȧ�������������������������������������������������������������
echo ��
echo ��
echo ��   ������Ʈ�� ����ũ����Ʈ ���������� �̿����ּż� �����Դ�.
echo ��
echo ��
echo ��   ������Ʈ�� �����Ⱑ ������ �̿��� �ڹٸ� �ڵ�����
echo ��      Ž���ϰ� �ֽ��ϴ�. ��ø� ��ٷ��ּ��� :D
echo ��
echo ��
echo ��  * ������� : ���� ������ �����Ͻ� �� stop ��ɾ ġ�ø�
echo ��                    ������ ���������� ����Ǵ� �������ּ���~
echo ��
echo ��
echo �Ʀ�������������������������������������������������������������

java -Xms1G -Xmx4G -jar [Forge]1.9.4_12.17.0.1968.jar
PAUSE
goto main


:RAM_8
cls
echo.
echo �Ȧ�������������������������������������������������������������
echo ��
echo ��
echo ��   ������Ʈ�� ����ũ����Ʈ ���������� �̿����ּż� �����Դ�.
echo ��
echo ��
echo ��   ������Ʈ�� �����Ⱑ ������ �̿��� �ڹٸ� �ڵ�����
echo ��      Ž���ϰ� �ֽ��ϴ�. ��ø� ��ٷ��ּ��� :D
echo ��
echo ��
echo ��  * ������� : ���� ������ �����Ͻ� �� stop ��ɾ ġ�ø�
echo ��                    ������ ���������� ����Ǵ� �������ּ���~
echo ��
echo ��
echo �Ʀ�������������������������������������������������������������

java -Xms1G -Xmx8G -jar [Forge]1.9.4_12.17.0.1968.jar
PAUSE
goto main


:RAM_16
cls
echo.
echo �Ȧ�������������������������������������������������������������
echo ��
echo ��
echo ��   ������Ʈ�� ����ũ����Ʈ ���������� �̿����ּż� �����Դ�.
echo ��
echo ��
echo ��   ������Ʈ�� �����Ⱑ ������ �̿��� �ڹٸ� �ڵ�����
echo ��      Ž���ϰ� �ֽ��ϴ�. ��ø� ��ٷ��ּ��� :D
echo ��
echo ��
echo ��  * ������� : ���� ������ �����Ͻ� �� stop ��ɾ ġ�ø�
echo ��                    ������ ���������� ����Ǵ� �������ּ���~
echo ��
echo ��
echo �Ʀ�������������������������������������������������������������

java -Xms1G -Xmx16G -jar [Forge]1.9.4_12.17.0.1968.jar
PAUSE
goto main


:JAVA64
cls
explorer "https://www.koreaminecraft.net/more_info/388965"
goto RAM


:blog
cls
explorer "http://freeroute.tistory.com/"
goto main

:way
cls
explorer https://www.koreaminecraft.net/server_tip/28048
goto main

:color
cls
echo.
echo �Ȧ�������������������������������������������������������
echo ��                                                                        
echo ��                                                                  
echo ��                �۾����� �����ϱ�                                                        
echo ��                                                                  
echo ��                                                                        
echo ��                                                                    
echo ��     1. ���                      2. �����                           
echo ��                                                                        
echo ��                                                                      
echo ��     3. ��ȫ��                    4. ������                           
echo ��                                                                           
echo ��                                                                        
echo ��     5. ���� ����                 6. ���� �ʷϻ�                      
echo ��                                                                        
echo ��                                                                      
echo ��     7. ���� �Ķ���               8. ȸ��                             
echo ��                                                                        
echo ��                                                                        
echo ��     9. ���� ȸ��                 10. Ȳ�ݻ�                          
echo ��                                                                        
echo ��                                                                        
echo ��     11. �����                   12. ��ο� ������                   
echo ��                                                                        
echo ��                                                                       
echo ��     13. ����                     14. ��ο� �ʷϻ�                   
echo ��                                                                        
echo ��                                                                       
echo ��     15. ��ο� �Ķ���            16 �������� �̵�              
echo ��
echo ��
echo ��
echo �Ʀ���������������������������������������������������������

set /p colorsetting=���ϴ� ������ ���� ���� �� Enter :
if /i "%colorsetting%"=="1" color 0f
if /i "%colorsetting%"=="2" color 0e
if /i "%colorsetting%"=="3" color 0d
if /i "%colorsetting%"=="4" color 0c
if /i "%colorsetting%"=="5" color 0b
if /i "%colorsetting%"=="6" color 0a
if /i "%colorsetting%"=="7" color 09
if /i "%colorsetting%"=="8" color 08
if /i "%colorsetting%"=="9" color 07
if /i "%colorsetting%"=="10" color 06
if /i "%colorsetting%"=="11" color 05
if /i "%colorsetting%"=="12" color 04
if /i "%colorsetting%"=="13" color 03
if /i "%colorsetting%"=="14" color 02
if /i "%colorsetting%"=="15" color 01
if /i "%colorsetting%"=="16" goto main

:error5
goto color

:freeroute
goto FreeRouteAPI