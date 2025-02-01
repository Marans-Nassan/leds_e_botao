
# Projeto: Controle de LEDs com Interrupção por Botão no Raspberry Pi Pico W

## Descrição do Projeto
Este projeto implementa um sistema para controlar três LEDs (vermelho, amarelo e verde) utilizando um Raspberry Pi Pico W (RP2040). O acendimento dos LEDs é acionado por uma interrupção gerada através de um botão, possibilitando a execução de uma sequência de acionamento onde cada LED permanece ligado por um tempo específico antes de ser desligado automaticamente.

## Objetivo
O objetivo principal deste projeto é demonstrar:
- Como configurar e utilizar interrupções no RP2040 para acionar ações.
- O controle sequencial de LEDs com ênfase em timers de alarme para definir o tempo de permanência de cada LED.
- A implementação de um mecanismo de debounce por software para evitar acionamentos indesejados.

## Funcionalidades

### Controle de LEDs
- **LED Vermelho (GPIO 11):** Acende inicialmente e integra a sequência de acionamento.
- **LED Amarelo (GPIO 12):** Acende após o LED vermelho, seguindo a sequência.
- **LED Verde (GPIO 13):** Acende após o LED amarelo, completando o ciclo.

### Interrupção por Botão
- **Botão (GPIO 5):** Ao ser pressionado (borda de descida), aciona uma interrupção que inicia a sequência de acionamento dos LEDs.

### Timers e Debounce
- **Timers de Alarme:** Cada LED é desligado após um delay específico (3s, 6s e 9s, respectivamente) utilizando a função `add_alarm_in_ms`.
- **Debounce por Software:** Implementação de um controle de debounce (200 ms) para garantir que o acionamento do botão seja confiável.

## Estrutura do Código

### Definições e Inicialização
- **Definição dos Pinos:** Configuração dos pinos GPIO para o botão e para os LEDs.
- **Inicialização do Botão:** Configuração do botão no modo de entrada com pull-up.
- **Inicialização dos LEDs:** Configuração dos LEDs no modo de saída e inicialização dos mesmos no estado desligado.

### Funções Principais
- **Callback do Alarme (`turn_off_callback`):** Desliga o LED correspondente após o tempo definido e atualiza o status dos LEDs.
- **Manipulador da Interrupção (`gpio_irq_handler`):** Detecta o acionamento do botão, realiza a verificação de debounce e inicia a sequência de acionamento dos LEDs, agendando o desligamento com os timers de alarme.
- **Loop Principal:** Mantém o programa em execução, permitindo que as interrupções sejam processadas.

## Requisitos de Hardware
- **Raspberry Pi Pico W (RP2040)**
- **Botão:** Conectado ao GPIO 5
- **LEDs:**
  - Vermelho: Conectado ao GPIO 11
  - Amarelo: Conectado ao GPIO 12
  - Verde: Conectado ao GPIO 13
- **Resistores de 330Ω:** Um para cada LED

## Requisitos de Software
- **SDK do Raspberry Pi Pico**
- **Ambiente de desenvolvimento configurado com suporte a C/C++**

## Como Usar

### Conecte o Hardware
1. Monte o circuito conforme os requisitos de hardware listados, conectando corretamente o botão e os LEDs aos respectivos GPIOs.

### Compile o Código
1. Configure o ambiente de desenvolvimento com o SDK do Raspberry Pi Pico.
2. Compile o código utilizando CMake ou outra ferramenta de build compatível.

### Carregue e Execute o Programa
1. Transfira o arquivo binário gerado para o Raspberry Pi Pico via USB.
2. Pressione o botão (GPIO 5) para iniciar a sequência de acionamento dos LEDs:
   - O LED vermelho acende e, após 3 segundos, é desligado.
   - O LED amarelo acende em seguida e permanece ligado por 3 segundos adicionais (totalizando 6 segundos).
   - Por fim, o LED verde acende e é desligado após 9 segundos.

## Exemplo de Sequência
Ao pressionar o botão, a sequência de acionamento e desligamento dos LEDs ocorre da seguinte forma:
- **0s:** LED vermelho aceso.
- **3s:** LED vermelho desligado, LED amarelo aceso.
- **6s:** LED amarelo desligado, LED verde aceso.
- **9s:** LED verde desligado.

## Contribuidor
Hugo Martins Santana (TIC370101267)

## Licença
Este projeto é disponibilizado sob a licença MIT. Consulte o arquivo LICENSE para mais informações.

---

*Nota: Este README foi elaborado para ser autoexplicativo, atendendo tanto iniciantes quanto especialistas em microcontroladores e sistemas embarcados.*