  /*************************************************************************
 * 
 *  ESP32 Logic Analyzer
 *  Copyright (C) 2025 lmcapacho (Luis Miguel Capacho V.)  
 *  Copyright (C) 2020 Erdem U. Altinyurt
 *    
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *************************************************************************
 *
 *  Dự án này sử dụng một phần mã nguồn từ:
 *  https://github.com/igrr/esp32-cam-demo (dành cho I2S DMA)
 *  và
 *  https://github.com/gillham/logic_analyzer/issues (dùng làm mẫu cho giao thức SUMP).
 * 
 */ 
#include "LogicAnalyzer.h"

LogicAnalyzer esp32la;

void setup(void) {
  esp32la.begin();
}

void loop()
{
  vTaskDelay(1); // Tránh lỗi WDT (Watchdog Timer - Bộ đếm thời gian giám sát)
  
  if (OLS_Port.available() > 0) {
    int cmdByte = OLS_Port.read();
    esp32la.handleCommand(cmdByte);    
  }
}

void IRAM_ATTR i2s_wrapper(void *arg)
{
  esp32la.i2s_isr(arg);
}
