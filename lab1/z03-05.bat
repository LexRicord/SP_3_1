@echo off
echo -- List of parameters: %1 %2 %3
echo -- Parameter 1: %1
echo -- Parameter 2: %2
echo -- Parameter 3: %3
set /a result_1 = %1 %3 %2
echo -- Result_1: %1 %3 %2 = %result_1%