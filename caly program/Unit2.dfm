object Form2: TForm2
  Left = 501
  Top = 293
  Width = 423
  Height = 483
  BorderStyle = bsSizeToolWin
  Caption = 'Ustawienia'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 208
    Top = 16
    Width = 185
    Height = 65
    Caption = 'Port'
    TabOrder = 0
    object ComboBox2: TComboBox
      Left = 16
      Top = 24
      Width = 145
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
    end
  end
  object GroupBox2: TGroupBox
    Left = 208
    Top = 88
    Width = 185
    Height = 105
    Caption = 'Dostep z internetu'
    TabOrder = 1
    object CheckBox1: TCheckBox
      Left = 8
      Top = 24
      Width = 161
      Height = 17
      Caption = 'Zezwol na dostep z internetu'
      TabOrder = 0
    end
    object LabeledEdit1: TLabeledEdit
      Left = 32
      Top = 64
      Width = 121
      Height = 21
      EditLabel.Width = 27
      EditLabel.Height = 13
      EditLabel.Caption = 'Haslo'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 1
    end
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 16
    Width = 193
    Height = 425
    Caption = 'Wlaczanie/wylaczanie automatyczne'
    TabOrder = 2
    object ComboBox1: TComboBox
      Left = 24
      Top = 24
      Width = 145
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 0
      Text = 'Przeka'#378'nik 1'
      OnChange = ComboBox1Change
      Items.Strings = (
        'Przeka'#378'nik 1'
        'Przeka'#378'nik 2'
        'Przeka'#378'nik 3'
        'Przeka'#378'nik 4'
        'Przeka'#378'nik 5'
        'Przeka'#378'nik 6'
        'Przeka'#378'nik 7'
        'Przeka'#378'nik 8')
    end
    object ListBox1: TListBox
      Left = 8
      Top = 56
      Width = 169
      Height = 353
      Hint = 'Kliknij aby dodac lub usunac czynnosc'
      ItemHeight = 13
      ParentShowHint = False
      PopupMenu = PopupMenu1
      ShowHint = True
      TabOrder = 1
    end
  end
  object GroupBox4: TGroupBox
    Left = 208
    Top = 216
    Width = 185
    Height = 121
    Caption = 'Nazwy przeka'#378'nikow'
    TabOrder = 3
    object SpeedButton1: TSpeedButton
      Left = 56
      Top = 88
      Width = 57
      Height = 25
      Caption = 'Zapisz'
      OnClick = SpeedButton1Click
    end
    object ComboBox3: TComboBox
      Left = 16
      Top = 24
      Width = 145
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 0
      Text = 'Przeka'#378'nik 1'
      OnChange = ComboBox3Change
      Items.Strings = (
        'Przeka'#378'nik 1'
        'Przeka'#378'nik 2'
        'Przeka'#378'nik 3'
        'Przeka'#378'nik 4'
        'Przeka'#378'nik 5'
        'Przeka'#378'nik 6'
        'Przeka'#378'nik 7'
        'Przeka'#378'nik 8')
    end
    object Edit1: TEdit
      Left = 24
      Top = 56
      Width = 121
      Height = 21
      TabOrder = 1
      Text = 'Edit1'
    end
  end
  object GroupBox5: TGroupBox
    Left = 208
    Top = 344
    Width = 185
    Height = 97
    Caption = 'Automatyczny start'
    TabOrder = 4
    object CheckBox2: TCheckBox
      Left = 8
      Top = 24
      Width = 137
      Height = 17
      Caption = 'Startuj z Windows'
      TabOrder = 0
    end
    object CheckBox3: TCheckBox
      Left = 8
      Top = 56
      Width = 145
      Height = 17
      Caption = 'Startuj zminimalizowany'
      TabOrder = 1
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 64
    Top = 104
    object Dodajczynno1: TMenuItem
      Caption = 'Dodaj czynnosc'
      OnClick = Dodajczynno1Click
    end
    object Usunczynnosc1: TMenuItem
      Caption = 'Usun czynnosc'
      OnClick = Usunczynnosc1Click
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object Usunwszystkie1: TMenuItem
      Caption = 'Usun wszystkie'
      OnClick = Usunwszystkie1Click
    end
  end
end
