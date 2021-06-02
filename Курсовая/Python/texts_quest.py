texts=[]
choose = 1
from PIL import ImageFont # new
import pygame
import config as c
class Texts_quest():
	def __init__(self,Q): # r_int вопрос в Q
		# print("init start")
		self.Q = Q
		self.fsize = 20
		self.font_gsize = ImageFont.truetype('verdana.ttf', self.fsize)
		self.texts = []
		self.font = pygame.font.SysFont('Verdana', self.fsize)

		self.sizes = []
		# print("start create")
		# self.texts.clear()
		choose = 1
		# self.create_text()
		# print("init fin")

	def get_font_size(self,text):
		return self.font_gsize.getsize(text)

	def create_text(self,r_int=0):
		self.r_int = r_int # от 0 до размера Q
		p=0
		for quest in self.Q[self.r_int]:
			# print(quest)

			color = quest['color']

			if p==1:
				color = "white"
			# self.texts.append(self.font.render(quest['namea'], True, quest['color']))
			self.texts.append([self.font.render(quest['namea'], True, color),quest['namea'], quest['color'],quest['status']])
			self.sizes.append(self.get_font_size(quest['namea']))
			j=0
			self.Max_h = 0
			self.Max_w = 0
			# print("cickle")
			while j<len(self.sizes):
				# print("inC")
				if j==0:
					j+=1
					continue

				if self.sizes[j][0]>self.Max_w:
					self.Max_w = self.sizes[j][0]
				if self.sizes[j][1]>self.Max_h:
					self.Max_h = self.sizes[j][1]
				j+=1
			p+=1

	def delete_text(self):
		self.texts.clear()
		self.sizes.clear()

	def spawn(self,surface,XY):
		self.surface = surface
		self.XY = XY
		i = 0
		for text in self.texts:

			# Границы, если слева 
			
			hals_sz_text = self.Max_w/2
			if i==0:
				hals_sz_text = self.sizes[i][0]/2
			


			if self.XY[0]<c.screen_width/2: # левая часть
				
				#Левая часть
				if self.XY[0] - hals_sz_text <0:
					pos  = (0 ,self.XY[1] + self.sizes[i][1]+i*self.Max_h)
					self.surface.blit(text[0], pos)
				else:
					pos  = (self.XY[0]- hals_sz_text,self.XY[1] + self.sizes[i][1]+i*self.Max_h)
					self.surface.blit(text[0], pos)
			else: # Правая часть

				#Правая часть
				if self.XY[0] + hals_sz_text >c.screen_width:
					pos  = (c.screen_width- hals_sz_text*2 ,self.XY[1] + self.sizes[i][1]+i*self.Max_h)
					self.surface.blit(text[0], pos)
				else:
					pos  = (self.XY[0]- hals_sz_text,self.XY[1] + self.sizes[i][1]+i*self.Max_h)
				self.surface.blit(text[0], pos)

			i+=1