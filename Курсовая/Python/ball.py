import pygame

from game_object import GameObject
from PIL import ImageFont # new
import config as c




# print(Q)
# Q = [ 
#     	[
#     	['Как называется ближайшая к Солнцу планета?','orange'],
#     	['Венера','red'],
#     	['Марс','deeppink'],
#     	['Меркурий','tomato'],
#     	['Земля','cyan']
#     	],

# 														      ]


class Ball(GameObject):
	def __init__(self, x, y, r, color, speed):
		# print("Создан Ball") # 3 раза - 3 жизни
		GameObject.__init__(self, x - r, y - r, r * 2, r * 2, speed)
		self.radius = r
		self.diameter = r * 2
		self.color = color
		# self.ClTextQ = Texts_quest(Q,0)
		# print("myclass, создан")


	def draw(self, surface): # отрисовывает каждое положение
		r = pygame.draw.circle(surface, self.color, self.center, self.radius)
		# print(Breakout.is_game_running)
		# if self.is_game_running:
		# 	self.ClTextQ.spawn(surface,self.center)

	def update(self):
		super().update()
