from datetime import datetime
import requests

def GetTime():
    now = datetime.now()
    current_time = now.strftime('%H:%M')
    current_day = now.strftime('%A')
    return current_day,current_time

def GetData(url):
    response = requests.get(url)
    json_str = response.json()
    data = json_str['feeds']
    temp = data[0]['field1'];humid = data[0]['field2'];co2 = data[0]['field3']
    return temp,humid,co2

def ConvertTime(timestring):
    hour = timestring.split(':')[0]
    min = timestring.split(':')[1]
    sec = timestring.split(':')[2]

    converted_string = '{}:{}:{}'.format(hour+7,min,sec)
    return converted_string

def ConvertDate(datestring):
    year = datestring.split('-')[0]
    month = datestring.split('-')[1]
    date = datestring.split('-')[2]

    converted_string = '{}/{}/{}'.format(date,month,year)
    return converted_string