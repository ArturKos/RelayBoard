object Form3: TForm3
  Left = 675
  Top = 193
  Width = 363
  Height = 627
  BorderStyle = bsSizeToolWin
  Caption = 'Wybierz akcje'
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
  object SpeedButton1: TSpeedButton
    Left = 48
    Top = 544
    Width = 81
    Height = 33
    Caption = 'OK'
    OnClick = SpeedButton1Click
  end
  object SpeedButton2: TSpeedButton
    Left = 208
    Top = 552
    Width = 81
    Height = 33
    Caption = 'Anuluj'
    OnClick = SpeedButton2Click
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 129
    Height = 81
    Caption = 'Akcja'
    TabOrder = 0
    object ComboBox1: TComboBox
      Left = 24
      Top = 32
      Width = 81
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 0
      Text = 'Wlacz'
      Items.Strings = (
        'Wlacz'
        'Wylacz')
    end
  end
  object GroupBox2: TGroupBox
    Left = 144
    Top = 8
    Width = 201
    Height = 81
    Caption = 'Godzina'
    TabOrder = 1
    object CSpinEdit1: TCSpinEdit
      Left = 16
      Top = 32
      Width = 41
      Height = 22
      TabOrder = 0
    end
    object CSpinEdit2: TCSpinEdit
      Left = 72
      Top = 32
      Width = 41
      Height = 22
      TabOrder = 1
    end
    object CSpinEdit3: TCSpinEdit
      Left = 136
      Top = 32
      Width = 41
      Height = 22
      TabOrder = 2
    end
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 96
    Width = 129
    Height = 201
    Caption = 'Dni tygodnia'
    TabOrder = 2
    object CheckBox1: TCheckBox
      Left = 16
      Top = 24
      Width = 97
      Height = 17
      Caption = 'Poniedzialek'
      TabOrder = 0
    end
    object CheckBox2: TCheckBox
      Left = 16
      Top = 48
      Width = 97
      Height = 17
      Caption = 'Wtorek'
      TabOrder = 1
    end
    object CheckBox3: TCheckBox
      Left = 16
      Top = 72
      Width = 97
      Height = 17
      Caption = 'Sroda'
      TabOrder = 2
    end
    object CheckBox4: TCheckBox
      Left = 16
      Top = 96
      Width = 97
      Height = 17
      Caption = 'Czwartek'
      TabOrder = 3
    end
    object CheckBox5: TCheckBox
      Left = 16
      Top = 120
      Width = 97
      Height = 17
      Caption = 'Piatek'
      TabOrder = 4
    end
    object CheckBox6: TCheckBox
      Left = 16
      Top = 144
      Width = 97
      Height = 17
      Caption = 'Sobota'
      TabOrder = 5
    end
    object CheckBox7: TCheckBox
      Left = 16
      Top = 168
      Width = 97
      Height = 17
      Caption = 'Niedziela'
      TabOrder = 6
    end
  end
  object GroupBox4: TGroupBox
    Left = 144
    Top = 96
    Width = 201
    Height = 201
    Caption = 'Dzailanie jednorazowe'
    TabOrder = 3
    object CheckBox8: TCheckBox
      Left = 16
      Top = 24
      Width = 129
      Height = 17
      Caption = 'Wykonaj tylko wtedy'
      TabOrder = 0
      OnClick = CheckBox8Click
    end
    object GroupBox5: TGroupBox
      Left = 16
      Top = 48
      Width = 169
      Height = 65
      Caption = 'Godzina'
      TabOrder = 1
      object LabeledEdit1: TLabeledEdit
        Left = 8
        Top = 32
        Width = 33
        Height = 21
        EditLabel.Width = 39
        EditLabel.Height = 13
        EditLabel.Caption = 'Godzina'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 0
      end
      object LabeledEdit2: TLabeledEdit
        Left = 64
        Top = 32
        Width = 41
        Height = 21
        EditLabel.Width = 32
        EditLabel.Height = 13
        EditLabel.Caption = 'Minuta'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 1
      end
      object LabeledEdit3: TLabeledEdit
        Left = 120
        Top = 32
        Width = 41
        Height = 21
        EditLabel.Width = 43
        EditLabel.Height = 13
        EditLabel.Caption = 'Sekunda'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 2
      end
    end
    object GroupBox6: TGroupBox
      Left = 16
      Top = 120
      Width = 169
      Height = 65
      Caption = 'Data'
      TabOrder = 2
      object LabeledEdit4: TLabeledEdit
        Left = 16
        Top = 32
        Width = 25
        Height = 21
        EditLabel.Width = 27
        EditLabel.Height = 13
        EditLabel.Caption = 'Dzien'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 0
      end
      object LabeledEdit5: TLabeledEdit
        Left = 56
        Top = 32
        Width = 33
        Height = 21
        EditLabel.Width = 36
        EditLabel.Height = 13
        EditLabel.Caption = 'Miesiac'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 1
      end
      object LabeledEdit6: TLabeledEdit
        Left = 104
        Top = 32
        Width = 49
        Height = 21
        EditLabel.Width = 20
        EditLabel.Height = 13
        EditLabel.Caption = 'Rok'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 2
      end
    end
  end
  object GroupBox7: TGroupBox
    Left = 8
    Top = 304
    Width = 337
    Height = 113
    Caption = 'Timer'
    TabOrder = 4
    object CheckBox9: TCheckBox
      Left = 16
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Wlacz'
      TabOrder = 0
    end
    object GroupBox8: TGroupBox
      Left = 16
      Top = 40
      Width = 137
      Height = 57
      Caption = 'Co jaki czas:'
      TabOrder = 1
      object Edit1: TEdit
        Left = 8
        Top = 24
        Width = 33
        Height = 21
        TabOrder = 0
        Text = 'Edit1'
      end
      object Edit2: TEdit
        Left = 48
        Top = 24
        Width = 33
        Height = 21
        TabOrder = 1
        Text = 'Edit2'
      end
      object Edit3: TEdit
        Left = 88
        Top = 24
        Width = 33
        Height = 21
        TabOrder = 2
        Text = 'Edit3'
      end
    end
    object GroupBox9: TGroupBox
      Left = 168
      Top = 40
      Width = 153
      Height = 57
      Caption = 'Na jaki czas:'
      TabOrder = 2
      object Edit4: TEdit
        Left = 8
        Top = 24
        Width = 33
        Height = 21
        TabOrder = 0
        Text = 'Edit4'
      end
      object Edit5: TEdit
        Left = 56
        Top = 24
        Width = 33
        Height = 21
        TabOrder = 1
        Text = 'Edit5'
      end
      object Edit6: TEdit
        Left = 104
        Top = 24
        Width = 33
        Height = 21
        TabOrder = 2
        Text = 'Edit6'
      end
    end
  end
  object GroupBox10: TGroupBox
    Left = 8
    Top = 424
    Width = 337
    Height = 113
    Caption = 'Losowa godzina'
    TabOrder = 5
    object CheckBox10: TCheckBox
      Left = 16
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Wlacz'
      TabOrder = 0
    end
    object GroupBox11: TGroupBox
      Left = 8
      Top = 40
      Width = 161
      Height = 57
      Caption = 'Nie krocej niz:'
      TabOrder = 1
      object Edit7: TEdit
        Left = 8
        Top = 24
        Width = 33
        Height = 21
        TabOrder = 0
        Text = 'Edit7'
      end
      object Edit8: TEdit
        Left = 56
        Top = 24
        Width = 33
        Height = 21
        TabOrder = 1
        Text = 'Edit8'
      end
      object Edit9: TEdit
        Left = 104
        Top = 24
        Width = 41
        Height = 21
        TabOrder = 2
        Text = 'Edit9'
      end
    end
    object GroupBox12: TGroupBox
      Left = 176
      Top = 40
      Width = 153
      Height = 57
      Caption = 'Nie dluzej niz'
      TabOrder = 2
      object Edit10: TEdit
        Left = 16
        Top = 24
        Width = 33
        Height = 21
        TabOrder = 0
        Text = 'Edit10'
      end
      object Edit11: TEdit
        Left = 64
        Top = 24
        Width = 33
        Height = 21
        TabOrder = 1
        Text = 'Edit11'
      end
      object Edit12: TEdit
        Left = 104
        Top = 24
        Width = 41
        Height = 21
        TabOrder = 2
        Text = 'Edit12'
      end
    end
  end
end
