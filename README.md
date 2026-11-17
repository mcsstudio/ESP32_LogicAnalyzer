# ESP32 LogicAnalyzer

![Trạng thái](https://img.shields.io/badge/Status-In%20Development-yellow)
![Giấy phép](https://img.shields.io/badge/License-GPL%203.0-blue)

Bộ phân tích logic 16 bit tương thích với [SUMP](http://dangerousprototypes.com/docs/The_Logic_Sniffer%27s_extended_SUMP_protocol), dành cho ESP32.

<img src="/docs/images/ESP32_LogicAnalyzer_in_PulseView.png" alt="PulseView" style="width: 80%;" />

## Thông số kỹ thuật

- Sử dụng **I2S DMA của ESP32** và có thể thu thập dữ liệu ở tốc độ lên đến **20 MHz**.
- Hỗ trợ chế độ hoạt động **8 bit** và **16 bit**.
- Tối đa **128k** mẫu (kể cả khi thu thập ở chế độ 8 bit).
- Hỗ trợ nén RLE.
- Cổng OLS mặc định là **UART0**, với tốc độ baud mặc định là **912600**.
- Bạn có thể cấu hình các cổng UART và tốc độ baud cao cho giao tiếp OLS bằng cách chỉnh sửa các định nghĩa trong `LogicAnalyzerConfig.h`.

### Môi trường được hỗ trợ

| Môi trường   | Trạng thái | Chi tiết                                      |
|--------------|------------|-----------------------------------------------|
| PlatformIO   | ✅         | Đã kiểm thử với `platform-espressif32@6.11.0` |
| Arduino IDE  | ✅         | Đã kiểm thử với `Arduino-ESP32 core 3.3.7`    |

### Đang phát triển

- Các mô-đun WROOVER hỗ trợ **2M** mẫu nhưng chỉ đạt tối đa **2 MHz** do giới hạn băng thông khi truy cập PSRAM.
- Hỗ trợ đầu vào analog.

## Hướng dẫn bắt đầu nhanh

### Môi trường

#### PlatformIO

1. Cài đặt [PlatformIO](https://platformio.org/) trong VS Code.
2. Mở thư mục dự án trong PlatformIO.
3. Biên dịch dự án và nạp chương trình vào ESP32.

#### Arduino IDE

1. Cài đặt **hỗ trợ bo mạch ESP32** thông qua Boards Manager (`esp32 by Espressif Systems`).
2. Mở sketch tại `ESP32_LogicAnalyzer/ESP32_LogicAnalyzer.ino`.
3. Chọn bo mạch bạn đang sử dụng (ví dụ: `ESP32 Dev Module`).
4. Sử dụng phiên bản ESP32 Arduino core `3.3.7`.
5. Nhấn **Upload**.

**Quan trọng:** Nếu dùng UART0 để giao tiếp OLS, hãy đặt **Core Debug Level = None** trong Arduino IDE trước khi biên dịch, đặc biệt khi thu thập dữ liệu ở tốc độ trên 10 MHz.

### PulseView

Mở PulseView bằng lệnh:
```bash
pulseview -D -d ols:conn=/dev/ttyUSB0::serialcomm=921600/8n1
```
Hoặc kết nối thiết bị từ giao diện đồ họa và chọn **Openbench Logic Sniffer & SUMP compatibles (ols)**.

![PulseView](/docs/images/connect_to_device_pulseview.png)

Có thể bật RLE trong hộp thoại cấu hình thiết bị:

![RLE](/docs/images/RLE_enable.png)

Để biết thêm chi tiết, xem [tài liệu PulseView](https://sigrok.org/wiki/PulseView).

## Kết nối

| Chân     | Kết nối                                      |
|----------|----------------------------------------------|
| clk_in   | GPIO23 (kết nối với **clk_out**)             |
| clk_out  | GPIO22 (kết nối với **clk_in**)              |
| Ground   | Kết nối GND của thiết bị cần đo với GND ESP32 |
| Channels | CH15 - CH0 (kết nối các tín hiệu tại đây)    |

<img src="/docs/images/esp32_la_conn.png" alt="Kết nối ESP32LA" style="width: 50%;" />

⚠️ **Cảnh báo:** GPIO23 được dùng làm xung clock đầu vào I2S và GPIO22 làm xung clock đầu ra LEDC.  
Không sử dụng các chân này cho mục đích I/O thông thường. Nếu cần, hãy thay đổi chúng trong mã nguồn và đấu dây lại tương ứng.

## Thiết kế phần cứng (KiCad)

Dự án này bao gồm một PCB tùy chỉnh được thiết kế bằng **KiCad 9** để kết nối ESP32 DevKitC V1 với các kênh của bộ phân tích logic và các bộ chuyển mức logic.

Tất cả tệp liên quan đến phần cứng nằm trong thư mục [`hardware/`](./hardware), bao gồm:

- Dự án KiCad hoàn chỉnh (`.kicad_pro`, `.kicad_sch`, `.kicad_pcb`)
- BOM (`BOM.xlsx`) và CPL (`CPL1.xlsx`) phục vụ lắp ráp
- Tệp Gerber (`hardware/gerbers/`) dùng để sản xuất PCB
- Cổng debug UART2 tùy chọn
- Các IC chuyển mức logic (SN74LVC245A) để tương thích với tín hiệu đầu vào 5V

> ⚠️ Thiết kế hiện đang trong quá trình kiểm định. Hãy tự chịu rủi ro khi sử dụng cho đến khi hoàn tất kiểm thử thực tế.

### Hình ảnh PCB

![Hình ảnh 3D của PCB](./hardware/images/pcb_3d.png)

## Ghi nhận đóng góp

Dự án này ban đầu do [Erdem U. Altinyurt](https://github.com/EUA) tạo ra.
Việt hóa do [mcsstudio](https://github.com/mcsstudio) dịch thuật, có sử dụng AI.

Dự án sử dụng mã nguồn từ:
- [esp32-cam-demo](https://github.com/igrr/esp32-cam-demo) cho I2S DMA.
- [Arduino Logic Analyzer](https://github.com/gillham/logic_analyzer) làm “khuôn mẫu” cho giao thức SUMP.

## Giấy phép

Dự án này được cấp phép theo **GPL 3.0**. Xem tệp [LICENSE](LICENSE) để biết chi tiết.
