@echo off
title 마인크래프트 1.9.4 스폰지 모드버킷 with 프리루트
:main
cls
echo.
echo ┍──────────────────────────────
echo │
echo │     프리루트의 마인크래프트 1.9.4 스폰지 모드버킷
echo │
echo │
echo │   1. 서버 만들기 (자동 자바 탐지)
echo │
echo │   2. 모드서버 여는 방법
echo │
echo │   3. 글씨색깔 변경하기
echo │
echo │   4. 프리루트 블로그 가기
echo │
echo │   5. 종료
echo │
echo │
echo │  * 핵심파일 제작 : SpongePowered / 서버구동기 제작 : 프리루트
echo │  * 핵심파일 버전 : 5.0.0 베타 1503
echo │  * 탑재된 포지 버전 : 12.17.0.1968
echo │  * 제작날짜 : 2017.04.13
echo │
echo ┕──────────────────────────────


set /p a=원하는 항목의 숫자를 입력하고 엔터(Enter) :
if %a%==1 goto RAM
if %a%==2 goto way
if %a%==3 goto color
if %a%==4 goto blog
if %a%==5 goto exit


:RAM
cls
echo.
echo ┍───────────────────────────────
echo │
echo │    서버를 여는데 사용하고자 하시는 램 용량을 선택해주세요
echo │
echo │
echo │    1. 램 512MB (저사양 컴퓨터)
echo │
echo │    2. 램 1GB (일반)
echo │
echo │    3. 램 2GB
echo │
echo │    4. 램 4GB
echo │
echo │    5. 램 8GB
echo │
echo │    6. 램 16GB
echo │
echo │
echo │  * 주의사항 1 : 램 2GB 이상 사용시, 컴퓨터에 반드시 자바 64비트
echo │                 버전"만" 설치되어 있어야 합니다 (설치:아래에 7 입력)
echo │
echo │  * 주의사항 2 : 컴퓨터에 장착되어있는 램보다 2~3GB 낮은 용량의
echo │                 램을 선택해서 서버에 사용하셔야 합니다
echo │
echo ┕───────────────────────────────


set /p b=원하는 램 용량 항목의 숫자를 입력하고 엔터(Enter) :
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
echo ┍───────────────────────────────
echo │
echo │
echo │   프리루트의 마인크래프트 서버파일을 이용해주셔서 감사함다.
echo │
echo │
echo │   프리루트의 구동기가 서버에 이용할 자바를 자동으로
echo │      탐지하고 있습니다. 잠시만 기다려주세요 :D
echo │
echo │
echo │  * 참고사항 : 이제 서버를 종료하실 때 stop 명령어를 치시면
echo │                    서버가 정상적으로 종료되니 참고해주세요~
echo │
echo │
echo ┕───────────────────────────────

java -Xms512M -Xmx512M -jar [Forge]1.9.4_12.17.0.1968.jar
PAUSE
goto main


:RAM_1
cls
echo.
echo ┍───────────────────────────────
echo │
echo │
echo │   프리루트의 마인크래프트 서버파일을 이용해주셔서 감사함다.
echo │
echo │
echo │   프리루트의 구동기가 서버에 이용할 자바를 자동으로
echo │      탐지하고 있습니다. 잠시만 기다려주세요 :D
echo │
echo │
echo │  * 참고사항 : 이제 서버를 종료하실 때 stop 명령어를 치시면
echo │                    서버가 정상적으로 종료되니 참고해주세요~
echo │
echo │
echo ┕───────────────────────────────

java -Xms1G -Xmx1G -jar [Forge]1.9.4_12.17.0.1968.jar
PAUSE
goto main


:RAM_2
cls
echo.
echo ┍───────────────────────────────
echo │
echo │
echo │   프리루트의 마인크래프트 서버파일을 이용해주셔서 감사함다.
echo │
echo │
echo │   프리루트의 구동기가 서버에 이용할 자바를 자동으로
echo │      탐지하고 있습니다. 잠시만 기다려주세요 :D
echo │
echo │
echo │  * 참고사항 : 이제 서버를 종료하실 때 stop 명령어를 치시면
echo │                    서버가 정상적으로 종료되니 참고해주세요~
echo │
echo │
echo ┕───────────────────────────────

java -Xms1G -Xmx2G -jar [Forge]1.9.4_12.17.0.1968.jar
PAUSE
goto main


:RAM_4
cls
echo.
echo ┍───────────────────────────────
echo │
echo │
echo │   프리루트의 마인크래프트 서버파일을 이용해주셔서 감사함다.
echo │
echo │
echo │   프리루트의 구동기가 서버에 이용할 자바를 자동으로
echo │      탐지하고 있습니다. 잠시만 기다려주세요 :D
echo │
echo │
echo │  * 참고사항 : 이제 서버를 종료하실 때 stop 명령어를 치시면
echo │                    서버가 정상적으로 종료되니 참고해주세요~
echo │
echo │
echo ┕───────────────────────────────

java -Xms1G -Xmx4G -jar [Forge]1.9.4_12.17.0.1968.jar
PAUSE
goto main


:RAM_8
cls
echo.
echo ┍───────────────────────────────
echo │
echo │
echo │   프리루트의 마인크래프트 서버파일을 이용해주셔서 감사함다.
echo │
echo │
echo │   프리루트의 구동기가 서버에 이용할 자바를 자동으로
echo │      탐지하고 있습니다. 잠시만 기다려주세요 :D
echo │
echo │
echo │  * 참고사항 : 이제 서버를 종료하실 때 stop 명령어를 치시면
echo │                    서버가 정상적으로 종료되니 참고해주세요~
echo │
echo │
echo ┕───────────────────────────────

java -Xms1G -Xmx8G -jar [Forge]1.9.4_12.17.0.1968.jar
PAUSE
goto main


:RAM_16
cls
echo.
echo ┍───────────────────────────────
echo │
echo │
echo │   프리루트의 마인크래프트 서버파일을 이용해주셔서 감사함다.
echo │
echo │
echo │   프리루트의 구동기가 서버에 이용할 자바를 자동으로
echo │      탐지하고 있습니다. 잠시만 기다려주세요 :D
echo │
echo │
echo │  * 참고사항 : 이제 서버를 종료하실 때 stop 명령어를 치시면
echo │                    서버가 정상적으로 종료되니 참고해주세요~
echo │
echo │
echo ┕───────────────────────────────

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
echo ┍────────────────────────────
echo │                                                                        
echo │                                                                  
echo │                글씨색깔 변경하기                                                        
echo │                                                                  
echo │                                                                        
echo │                                                                    
echo │     1. 흰색                      2. 노랑색                           
echo │                                                                        
echo │                                                                      
echo │     3. 분홍색                    4. 빨강색                           
echo │                                                                           
echo │                                                                        
echo │     5. 연한 옥색                 6. 밝은 초록색                      
echo │                                                                        
echo │                                                                      
echo │     7. 연한 파랑색               8. 회색                             
echo │                                                                        
echo │                                                                        
echo │     9. 연한 회색                 10. 황금색                          
echo │                                                                        
echo │                                                                        
echo │     11. 보라색                   12. 어두운 빨강색                   
echo │                                                                        
echo │                                                                       
echo │     13. 옥색                     14. 어두운 초록색                   
echo │                                                                        
echo │                                                                       
echo │     15. 어두운 파랑색            16 메인으로 이동              
echo │
echo │
echo │
echo ┕─────────────────────────────

set /p colorsetting=원하는 색깔의 숫자 적은 후 Enter :
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