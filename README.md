# DHA_3v1
# Những điều cần làm

- App MQTT cần có biến kiểu enum cập nhật trạng thái xem hoạt động bình thường hay đang lỗi giao tiếp. Biến này cần truy cập được từ main.
    Trạng thái 1: Đang khởi tạo giao tiếp.
    Trạng thái 2: Giao tiếp bình thường
    Trạng thái 3: Lỗi
- Mở rộng thêm: Khi giao tiếp bình thường thì có 2 quá trình: publish và subcribe.
- Cần cập nhật được từ main để main biết và nháy LED báo đang gửi hay nhận.
- Cần thêm chức năng gửi nhận. Mà message gửi nhận cần truy cập được từ bên ngoài.
- Fix lại những gì chạy cài đặt ở trên apps, còn service chỉ như bộ thư viện.

Đang thêm các biến trạng thái để hiển thị ra LEDs các trạng thái của EG800K và trạng thái giao tiếp MQTT.