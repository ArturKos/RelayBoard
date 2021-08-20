object Form1: TForm1
  Left = 333
  Top = 187
  Width = 371
  Height = 402
  Caption = 'Klient SterowanieListwa'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object SpeedButton2: TSpeedButton
    Left = 192
    Top = 24
    Width = 113
    Height = 25
    Caption = 'Polacz'
    OnClick = SpeedButton2Click
  end
  object SpeedButton1: TSpeedButton
    Left = 24
    Top = 104
    Width = 113
    Height = 41
    AllowAllUp = True
    GroupIndex = 1
    OnClick = SpeedButton1Click
  end
  object SpeedButton3: TSpeedButton
    Left = 192
    Top = 104
    Width = 113
    Height = 41
    AllowAllUp = True
    GroupIndex = 2
    OnClick = SpeedButton3Click
  end
  object SpeedButton4: TSpeedButton
    Left = 24
    Top = 152
    Width = 113
    Height = 41
    AllowAllUp = True
    GroupIndex = 3
    OnClick = SpeedButton4Click
  end
  object SpeedButton5: TSpeedButton
    Left = 192
    Top = 152
    Width = 113
    Height = 41
    AllowAllUp = True
    GroupIndex = 4
    OnClick = SpeedButton5Click
  end
  object SpeedButton6: TSpeedButton
    Left = 24
    Top = 200
    Width = 113
    Height = 41
    AllowAllUp = True
    GroupIndex = 5
    OnClick = SpeedButton6Click
  end
  object SpeedButton7: TSpeedButton
    Left = 192
    Top = 200
    Width = 113
    Height = 41
    AllowAllUp = True
    GroupIndex = 6
    OnClick = SpeedButton7Click
  end
  object SpeedButton8: TSpeedButton
    Left = 24
    Top = 248
    Width = 113
    Height = 41
    AllowAllUp = True
    GroupIndex = 7
    OnClick = SpeedButton8Click
  end
  object SpeedButton9: TSpeedButton
    Left = 192
    Top = 248
    Width = 113
    Height = 41
    AllowAllUp = True
    GroupIndex = 8
    OnClick = SpeedButton9Click
  end
  object SpeedButton10: TSpeedButton
    Left = 112
    Top = 304
    Width = 111
    Height = 38
    AllowAllUp = True
    GroupIndex = 9
    Caption = 'Wszystkie'
    OnClick = SpeedButton10Click
  end
  object LabeledEdit1: TLabeledEdit
    Left = 16
    Top = 24
    Width = 153
    Height = 21
    EditLabel.Width = 78
    EditLabel.Height = 13
    EditLabel.Caption = 'Adres IP servera'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 0
    Text = '127.0.0.1'
  end
  object LabeledEdit2: TLabeledEdit
    Left = 16
    Top = 64
    Width = 153
    Height = 21
    EditLabel.Width = 80
    EditLabel.Height = 13
    EditLabel.Caption = 'Haslo do servera'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 1
  end
  object client: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 1212
    OnConnect = clientConnect
    OnDisconnect = clientDisconnect
    OnRead = clientRead
    OnError = clientError
    Left = 312
    Top = 24
  end
end
