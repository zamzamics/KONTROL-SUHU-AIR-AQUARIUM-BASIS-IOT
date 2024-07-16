const int sensorPin = A0; // Pin analog untuk sensor cahaya (LDR)
const int relayPin = 2;   // Pin digital untuk relay

int lightThreshold = 500; // Ambang batas untuk menentukan kapan lampu harus menyala/mati

void setup() {
  pinMode(sensorPin, INPUT);   // Mengatur pin sensor sebagai input
  pinMode(relayPin, OUTPUT);   // Mengatur pin relay sebagai output
}

void loop() {
  int lightValue = analogRead(sensorPin); // Membaca nilai sensor cahaya

  // Memeriksa apakah nilai sensor cahaya di bawah ambang batas
  if (lightValue < lightThreshold) {
    // Jika kondisi gelap, aktifkan relay untuk menyalakan lampu
    digitalWrite(relayPin, HIGH); // Menyalakan relay (mengaktifkan lampu)
  } else {
    // Jika kondisi terang, matikan relay untuk mematikan lampu
    digitalWrite(relayPin, LOW); // Mematikan relay (mematikan lampu)
  }

  delay(100); // Jeda untuk stabilitas bacaan sensor
}
