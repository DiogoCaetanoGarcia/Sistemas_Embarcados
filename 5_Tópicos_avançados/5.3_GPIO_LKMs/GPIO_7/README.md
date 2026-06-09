# Device Tree e GPIO com DTS no Linux

## 1 — O que é Device Tree?

**Device Tree (DT)** é uma estrutura de dados que descreve o hardware da placa.

Ele responde perguntas como:

- Quais dispositivos existem?
- Em quais endereços estão?
- Quais GPIOs utilizam?
- Quais interrupções utilizam?

Ideia principal:

```text
Hardware
    ↓
Device Tree
    ↓
Drivers
```

---

## 2 — Por que o Device Tree existe?

Sem Device Tree:

```c
#define LED_GPIO 4
gpio_to_desc(512 + LED_GPIO);
```

Problemas:

- Driver depende da placa.
- Mudança de hardware exige recompilar.
- O mesmo driver não funciona em outra plataforma.

Exemplo:

```text
Raspberry Pi → GPIO4
Placa X      → GPIO12
Placa Y      → GPIO31
```

---

## 3 — Antes do Device Tree

Antigamente os drivers faziam:

```c
#define GPIO_RESET 17
#define GPIO_LED   4
```

O hardware ficava embutido no código.

Consequência:

```text
Novo hardware
      ↓
Modificar driver
      ↓
Recompilar
```

---

## 4 — Com Device Tree

Agora o driver não conhece o hardware.

Driver:

```c
gpiod_get(dev, "reset", ...);
```

Device Tree:

```dts
reset-gpios = <&gpio 17 0>;
```

ou:

```dts
reset-gpios = <&gpio 31 0>;
```

O driver continua exatamente igual.

---

## 5 — O que é um arquivo DTS?

Arquivo texto:

```dts
/dts-v1/;

/ {
        ...
};
```

Extensão:

```text
.dts
```

Compilado para:

```text
.dtb
```

(Device Tree Blob)

---

## 6 — Exemplo Simples

```dts
led {
        my-led-gpios = <&gpio 4 0>;
};
```

Significado:

```text
&gpio  → controlador GPIO
4      → GPIO4 BCM
0      → ativo em nível alto
```

---

## 7 — Device Tree Overlay

O Raspberry Pi normalmente utiliza overlays.

Arquivo:

```text
gpiomod_output-overlay.dts
```

Compilação:

```bash
dtc -@ -I dts -O dtb -o gpiomod_output.dtbo gpiomod_output-overlay.dts
```

Resultado:

```text
.dtbo
```

(overlay carregável)

---

## 8 — Nosso Overlay

Trecho principal:

```dts
gpiomod_output {
        compatible = "soe,gpiomod-output";
        my-led-gpios = <&gpio 4 0>;
};
```

Ele cria um novo dispositivo chamado:

```text
gpiomod_output
```

e informa que:

```text
my-led → GPIO4
```

---

## 9 — O campo compatible

Device Tree:

```dts
compatible = "soe,gpiomod-output";
```

Driver:

```c
{ .compatible = "soe,gpiomod-output" }
```

O kernel utiliza essa string para conectar:

```text
Device Tree
      ↔
Driver
```

---

## 10 — O que acontece no boot?

Fluxo:

```text
Bootloader
      ↓
Kernel
      ↓
Carrega Device Tree
      ↓
Encontra compatible
      ↓
Chama probe()
```

---

## 11 — A função probe()

Quando o kernel encontra:

```text
soe,gpiomod-output
```

ele executa:

```c
gpiomod_probe(...)
```

Nesse momento o driver pode acessar os recursos descritos no DT.

---

## 12 — Obtendo o GPIO

Código:

```c
led = devm_gpiod_get(&pdev->dev, "my-led", GPIOD_OUT_HIGH);
```

O kernel procura automaticamente:

```dts
my-led-gpios = <&gpio 4 0>;
```

e devolve o descritor GPIO.

---

## 13 — Comparação com GPIO_1

GPIO_1:

```c
gpio_to_desc(512 + 4);
```

GPIO_7:

```c
devm_gpiod_get(..., "my-led", ...)
```

No GPIO_7 o driver não conhece:

- GPIO4
- BCM2835
- base 512

Tudo vem do Device Tree.

---

## 14 — Resumo

```text
Overlay DTS
      ↓
compatible
      ↓
platform_driver
      ↓
probe()
      ↓
devm_gpiod_get()
      ↓
LED ON
```

Mensagem principal:

> Nos exemplos anteriores o driver procurava diretamente o GPIO. No exemplo com Device Tree, o driver procura apenas um recurso chamado "my-led"; o Device Tree informa ao kernel qual pino físico deve ser utilizado.
