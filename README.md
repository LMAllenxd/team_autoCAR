# 自走車專案
本專案結合紅外線循跡與超音波避障，讓 Arduino 控制的自走車能在黑線路徑上行駛並自動避開前方障礙物。
---

## 一、專案特色
hhh
---

## 二、硬體需求
hhh
### 腳位對應

| 功能             | 腳位         |
| ---------------- | ------------ |
| ENA (左馬達 PWM) | D3           |
| IN1, IN2 (左輪)  | D2, D4       |
| ENB (右馬達 PWM) | D5           |
| IN3, IN4 (右輪)  | D6, D7       |
| IR_left, IR_right| D9, D8       |
| TRIG, ECHO       | D10, D11     |
| LED_LEFT, LED_RIGHT | D12, D13 |
---
## 三、軟體結構

```
sketch_apr8a/
├── 000.ino          // 主程式：初始化、主 Loop
├── planning.md      // 邏輯規劃文件
└── README.md        // 使用說明
```

### 核心函式

- `void forward()`：前進並亮雙燈
- `void turnLeft()`、`void turnRight()`：原地轉彎並亮對應 LED
- `void backward()`：後退並熄滅 LED
- `void stopMotors()`：停止四輪並熄滅 LED
- `long readUltrasonic()`：讀取超音波距離值

---

## 四、安裝與上傳

1. 下載或複製本專案至 Arduino IDE。
2. 選擇對應開發板 (Arduino Uno) 與序列埠。
3. 點擊「上傳」編譯並燒錄至主控板。

---

## 五、參數調整

- **MOTOR_SPEED**：前進速度 (0~255)
- **TURN_SPEED**：轉彎與後退速度
- **距離閾值**：`if (distance < 20)` 中的 20 cm
- **延遲時間**：避障後退與轉彎的 `delay()` 長度
