from kivy.uix.label import Label
from kivymd.uix.boxlayout import BoxLayout
from kivymd.uix.floatlayout import FloatLayout
from kivy.graphics.vertex_instructions import Rectangle
from kivymd.uix.bottomnavigation import MDBottomNavigation,MDBottomNavigationItem
from screen import ScrManager

icon = {'temp':'thermometer-lines','humid':'water','co2':'molecule-co2','air':'weather-windy-variant'}

class ClockWidget(BoxLayout):
    def __init__(self,weekday,time,**kwargs):
        super(ClockWidget,self).__init__(**kwargs)
        self.orientation = 'vertical'
        self.text = '{} - {}'.format(weekday,time)
        self.location_label = Label(text = 'Hanoi',font_size = self.height * 0.3)
        self.time_label = Label(text = self.text,font_size = self.height * 0.2)

        self.add_widget(self.location_label)
        self.add_widget(self.time_label)

class OptionBar(MDBottomNavigation):
    def __init__(self,**kwargs):
        super(OptionBar,self).__init__(**kwargs)

        self.temp_button = MDBottomNavigationItem(text = 'temp',icon = icon['temp'])
        self.humid_button = MDBottomNavigationItem(text = 'humid',icon = icon['humid'])
        self.co2_button = MDBottomNavigationItem(text = 'co2',icon = icon['co2'])
        self.all_button = MDBottomNavigationItem(text = 'air', icon=icon['air'])

        self.add_widget(self.temp_button)
        self.add_widget(self.humid_button)
        self.add_widget(self.co2_button)
        self.add_widget(self.all_button)

class RootWidget(FloatLayout):
    def __init__(self,background,**kwargs):
        super(RootWidget, self).__init__(**kwargs)
        with self.canvas.before:
            self.rect = Rectangle(source = background,pos = self.pos,size = self.size)

        self.bind(pos = self.update_rect)
        self.bind(size = self.update_rect)

        self.clock = ClockWidget(weekday = 'Unknow',time = '--:--',size_hint = (.5,.2),pos_hint = {'top':1,'center_x':.5})
        self.display = ScrManager(size_hint = (1,.7),pos_hint = {'center_y':.45})

        self.option = OptionBar(size_hint = (1,.05),pos_hint = {'bot':0})
        self.option.temp_button.bind(on_tab_press = self.temp_press)
        self.option.humid_button.bind(on_tab_press = self.humid_press)
        self.option.co2_button.bind(on_tab_press = self.co2_press)
        self.option.all_button.bind(on_tab_press = self.all_press)

        self.add_widget(self.clock)
        self.add_widget(self.display)
        self.add_widget(self.option)

    def temp_press(self,*args):
        self.display.current = 'temp_screen'

    def humid_press(self,*args):
        self.display.current = 'humid_screen'

    def co2_press(self,*args):
        self.display.current = 'co2_screen'

    def all_press(self,*args):
        self.display.current = 'air_screen'

    def update_rect(self,*args):
        self.rect.pos = self.pos
        self.rect.size = (self.size[0],self.size[1])