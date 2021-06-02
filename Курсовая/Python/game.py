

import pygame
import sys

from collections import defaultdict


class Game:
    def __init__(self, caption, width, height, back_image_filename, frame_rate):
        self.background_image = pygame.image.load(back_image_filename)
        self.frame_rate = frame_rate
        self.game_over = False
        self.objects = []
        pygame.mixer.init(44100, -16, 2, 4096)
        pygame.init()
        pygame.font.init()
        self.surface = pygame.display.set_mode((width, height))
        pygame.display.set_caption(caption)
        self.clock = pygame.time.Clock()
        self.keydown_handlers = defaultdict(list)
        self.keyup_handlers = defaultdict(list)
        self.mouse_handlers = []

        self.choose = 1
        self.last_choose = 1
        self.is_answere_true = False

    def update(self):
        for o in self.objects:
            o.update()

    def draw(self):
        for o in self.objects:
            o.draw(self.surface)

    def handle_events(self):
        global choose,texts
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                for handler in self.keydown_handlers[event.key]:
                    handler(event.key)



                if self.is_game_running:    
                    if event.key == pygame.K_DOWN:
                        print("up")
                        # font = pygame.font.SysFont('Verdana', 20)# вынести в конфиг size
                        # texts[choose][0] = font.render(texts[choose][1], True, texts[choose][2])# Истина цвет
                        if self.choose == 4:
                            self.choose = 1
                        else:
                            self.choose +=1 
                        # texts[choose][0] = font.render(texts[choose][1], True, "white")# Белый цвет

                    if event.key == pygame.K_UP:
                        print("down")
                        # font = pygame.font.SysFont('Verdana', 20)# вынести в конфиг size
                        # texts[choose][0] = font.render(texts[choose][1], True, texts[choose][2])# Истина цвет

                        if self.choose == 1:
                            self.choose = 4
                        else:
                            self.choose -=1 
                        # texts[choose][0] = font.render(texts[choose][1], True, "white")# Белый цвет


                    if event.key == pygame.K_RETURN and len(self.TextQuest.texts) != 0:
                        if self.TextQuest.texts[self.choose][3]==str(1):
                            self.is_answere_true = True

                            print("Верно")
                        else:
                            self.is_answere_False = True
                            print("неверно")





            elif event.type == pygame.KEYUP:
                for handler in self.keyup_handlers[event.key]:
                    handler(event.key)
            elif event.type in (pygame.MOUSEBUTTONDOWN, pygame.MOUSEBUTTONUP, pygame.MOUSEMOTION):
                for handler in self.mouse_handlers:
                    handler(event.type, event.pos)



    def run(self):
        while not self.game_over:
            self.surface.blit(self.background_image, (0, 0))

            self.handle_events()
            self.update()
            self.draw()

            pygame.display.update()
            self.clock.tick(self.frame_rate)
        import time
        time.sleep(5) # Задержка перед закрытием, чтобы посомтреть на результат
