from kivymd.app import MDApp
from kivy.core.window import Window
from app_component import *
from utils import GetTime,GetData
from kivy.clock import Clock

#create app window
Window.size = (470,700)

#define app feature
app_icon = 'app_icon.jpg'
app_title = 'Air Quality Monitoring System'
app_background = 'image.jpg'

#define url to get data from
id = '1634163'
api_key = 'SA2USU83PYQIGKI7'

url = 'https://api.thingspeak.com/channels/{}/feeds.json?api_key={}&results=1'.format(id,api_key)

class MainApp(MDApp):
    def __init__(self,**kwargs):
        super(MainApp,self).__init__(**kwargs)

    def app_config(self,title,icon,background):
        self.background = background
        self.icon = icon
        self.title = title

    def build(self):
        self.root = RootWidget(background = self.background)
        Clock.schedule_interval(self.update_screen,30)
        return self.root

    def update_screen(self,*args):
        self.update_time()
        self.update_data()

    def update_time(self,*args):
        week_day, time = GetTime()
        text = '{} - {}'.format(week_day,time)
        self.root.clock.time_label.text = text

    def update_data(self,*args):
        temp, humid, co2 = GetData(url)
        if int(co2) < 400:
            quality = 'GOOD'
        else:
            quality = 'BAD'

        temp = '{}°C'.format(temp)
        humid = '{}%'.format(humid)

        self.root.display.temp_screen.label.text = temp
        self.root.display.humid_screen.label.text = humid
        self.root.display.co2_screen.label.text = co2
        self.root.display.air_screen.label.text = quality

if __name__ == "__main__":
    App = MainApp()
    App.app_config(title = app_title,
                   icon = app_icon,
                   background = app_background
                   )
    App.run()