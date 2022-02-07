from kivy.uix.screenmanager import Screen,ScreenManager
from kivy.uix.label import Label
from kivy.graphics.context_instructions import Color
from kivy.graphics.vertex_instructions import Ellipse

text_color = (115/255,44/255,82/255,0.8)

class TempScreen(Screen):
    def __init__(self,**kwargs):
        super(TempScreen,self).__init__(**kwargs)
        self.label = Label(text = '...',font_size = self.height * 0.6,color = text_color)
        self.add_widget(self.label)
        with self.canvas.before:
            Color(1,1,1,.2)
            self.ellipse = Ellipse(pos = self.pos,size = self.size)

        self.bind(pos = self.update_ellipse)
        self.bind(size = self.update_ellipse)

    def update_ellipse(self,*args):
        self.ellipse.pos = (self.size[0] * 0.25,self.size[1] * 0.25)
        self.ellipse.size = (self.size[0] * 0.5,self.size[1] * 0.5)

class HumidScreen(Screen):
    def __init__(self,**kwargs):
        super(HumidScreen,self).__init__(**kwargs)
        self.label = Label(text = '...',font_size = self.height * 0.6,color = text_color)
        self.add_widget(self.label)
        with self.canvas.before:
            Color(1,1,1,.2)
            self.ellipse = Ellipse(pos = self.pos,size = self.size)

        self.bind(pos = self.update_ellipse)
        self.bind(size = self.update_ellipse)

    def update_ellipse(self,*args):
        self.ellipse.pos = (self.size[0] * 0.25,self.size[1] * 0.25)
        self.ellipse.size = (self.size[0] * 0.5,self.size[1] * 0.5)

class Co2Screen(Screen):
    def __init__(self,**kwargs):
        super(Co2Screen,self).__init__(**kwargs)
        self.label = Label(text='...',font_size = self.height * 0.6,color = text_color)
        self.add_widget(self.label)
        with self.canvas.before:
            Color(1,1,1,.2)
            self.ellipse = Ellipse(pos = self.pos,size = self.size)

        self.bind(pos=self.update_ellipse)
        self.bind(size=self.update_ellipse)

    def update_ellipse(self,*args):
        self.ellipse.pos = (self.size[0] * 0.25, self.size[1] * 0.25)
        self.ellipse.size = (self.size[0] * 0.5, self.size[1] * 0.5)


class AirScreen(Screen):
    def __init__(self,**kwargs):
        super(AirScreen,self).__init__(**kwargs)
        self.label = Label(text='...',font_size = self.height * 0.6,color = text_color)
        self.add_widget(self.label)
        with self.canvas.before:
            Color(1, 1, 1,.2)
            self.ellipse = Ellipse(pos=self.pos, size=self.size)

        self.bind(pos = self.update_ellipse)
        self.bind(size = self.update_ellipse)

    def update_ellipse(self,*args):
        self.ellipse.pos = (self.size[0] * 0.25,self.size[1] * 0.25)
        self.ellipse.size = (self.size[0] * 0.5,self.size[1] * 0.5)


class ScrManager(ScreenManager):
    def __init__(self,**kwargs):
        super(ScrManager,self).__init__(**kwargs)
        self.temp_screen = TempScreen(name = 'temp_screen')
        self.humid_screen = HumidScreen(name = 'humid_screen')
        self.co2_screen = Co2Screen(name = 'co2_screen')
        self.air_screen = AirScreen(name = 'air_screen')

        self.add_widget(self.temp_screen)
        self.add_widget(self.humid_screen)
        self.add_widget(self.co2_screen)
        self.add_widget(self.air_screen)