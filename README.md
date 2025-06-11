# 自走車專案
本專案結合紅外線循跡與超音波避障，讓 Arduino 控制的自走車能在黑線路徑上行駛並自動避開前方障礙物。
---

## 一、專案特色
### - 循跡功能
#### 利用兩顆紅外線感測器（左 IR、右 IR）判斷是否偏離路線，並做出左右修正或前進動作。
### - 避障功能
#### 使用超音波模組偵測前方距離，若小於 15 cm 則停止前進，直到障礙物清除為止。
### - 序列顯示（代替 LED 顯示）
#### 目前使用 Serial.println() 顯示狀態，可改接 OLED 或 LED 作為視覺提示。
### - 轉彎強化功能
#### 轉彎時提升其中一輪的速度（加上 rotateSpeedBuff）以加強修正效果。
---

## 二、硬體需求
- Arduino Uno (或相容開發板)
- L298N 雙 H 橋馬達驅動板
- 2x 紅外線循跡感測器 (IR modules)
- 1x HC-SR04 超音波感測器
- 4x 直流馬達 + 車輪套件
- 2x LED 指示燈
- 1x 4AA電池盒
- 1x 8AA電池盒
- 12x AA電池
- 一堆杜邦線（公對公、母對母、公對母）
- 一個不停調參數的耐心
### 腳位對應

| 功能             | 腳位         |
| ---------------- | ------------ |
| ENA (左馬達 PWM) | D3           |
| IN1, IN2 (左輪)  | D2, D4       |
| ENB (右馬達 PWM) | D5           |
| IN3, IN4 (右輪)  | D6, D7       |
| 紅外線感測器IR_left, IR_right| D8, D9       |
| 超音波模組TRIG, ECHO       | D11, D10     |
| LED_LEFT, LED_RIGHT | D12, D13 |
---
## 三、軟體結構

```
sketch_apr8a/
├── code.ino          // 主程式：初始化、主 Loop
├── 邏輯規劃.md      // 邏輯規劃文件
└── README.md        // 使用說明
```

### 核心函式

- `void forward()`：前進並亮雙燈
- `void setup() `：設定腳位模式
- `void turnLeft()`、`void turnRight()`：原地轉彎並亮對應 LED
- `void stopMotors()`：停止四輪並熄滅 LED
- `long readUltrasonic()`：讀取超音波距離值

---

## 四、安裝與上傳

1. 下載或複製本專案至 Arduino IDE。
2. 選擇對應開發板 (Arduino Uno) 與序列埠。
3. 點擊「上傳」編譯並燒錄至主控板。

---

## 五、參數調整

- **int leftSpeed**：左轉速度 (50~100)
- **int rightSpeed**：右轉速度 (50~100)
- **int rotateSpeedBuff**：前進加速度 (35~40)
- **距離閾值**：`if (distance < 15)` 中的 15 cm
- **延遲時間**：避障後退與轉彎的 `delay()` 長度
- **每次循環的間隔**：`delay(27)`控制感測頻率與執行節奏
