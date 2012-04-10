object MainForm: TMainForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = #1051#1072#1073#1086#1088#1072#1090#1086#1088#1085#1072#1103' '#1088#1072#1073#1086#1090#1072' '#8470'1 | '#1071#1089#1085#1086#1074' '#1053#1080#1082#1086#1083#1072#1081' '#1075#1088'. 8306'
  ClientHeight = 562
  ClientWidth = 1008
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Graph: TImage
    Left = 8
    Top = 31
    Width = 855
    Height = 523
    OnMouseDown = GraphMouseDown
    OnMouseMove = GraphMouseMove
    OnMouseUp = GraphMouseUp
  end
  object Label1: TLabel
    Left = 869
    Top = 128
    Width = 45
    Height = 13
    Caption = #1052#1072#1089#1096#1090#1072#1073
  end
  object ActionMainMenuBar1: TActionMainMenuBar
    Left = 0
    Top = 0
    Width = 1008
    Height = 25
    UseSystemFont = False
    ActionManager = ActionManager1
    Caption = 'ActionMainMenuBar1'
    Color = clMenuBar
    ColorMap.DisabledFontColor = 7171437
    ColorMap.HighlightColor = clWhite
    ColorMap.BtnSelectedFont = clBlack
    ColorMap.UnusedColor = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    Spacing = 0
  end
  object DrawBtn: TButton
    Left = 869
    Top = 175
    Width = 131
    Height = 25
    Caption = #1053#1072#1088#1080#1089#1086#1074#1072#1090#1100
    TabOrder = 1
    OnClick = DrawBtnClick
  end
  object ReflectionSurfaceSelect: TRadioGroup
    Left = 869
    Top = 31
    Width = 131
    Height = 90
    Caption = #1055#1083#1086#1089#1082#1086#1089#1090#1100' '#1086#1090#1088#1072#1078#1077#1085#1080#1103
    ItemIndex = 0
    Items.Strings = (
      #1041#1077#1079' '#1086#1090#1088#1072#1078#1077#1085#1080#1103
      'X-Y'
      'Y-Z'
      'X-Z')
    TabOrder = 2
  end
  object GroupBox1: TGroupBox
    Left = 870
    Top = 222
    Width = 130
    Height = 123
    Caption = #1051#1077#1075#1077#1085#1076#1072
    TabOrder = 3
    object ColorX: TImage
      Left = 16
      Top = 24
      Width = 25
      Height = 25
    end
    object ColorY: TImage
      Left = 16
      Top = 55
      Width = 25
      Height = 25
    end
    object ColorZ: TImage
      Left = 16
      Top = 86
      Width = 25
      Height = 25
    end
    object Label4: TLabel
      Left = 56
      Top = 24
      Width = 36
      Height = 13
      Caption = #1054#1089#1100' OX'
    end
    object Label5: TLabel
      Left = 56
      Top = 56
      Width = 36
      Height = 13
      Caption = #1054#1089#1100' OY'
    end
    object Label10: TLabel
      Left = 56
      Top = 88
      Width = 36
      Height = 13
      Caption = #1054#1089#1100' OZ'
    end
  end
  object ScaleEdit: TCSpinEdit
    Left = 869
    Top = 147
    Width = 131
    Height = 22
    MaxValue = 100
    MinValue = 1
    TabOrder = 4
  end
  object Button1: TButton
    Left = 240
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 5
    OnClick = Button1Click
  end
  object ActionManager1: TActionManager
    ActionBars = <
      item
        Items = <
          item
            Action = Open
            Caption = '&'#1054#1090#1082#1088#1099#1090#1100
          end>
        ActionBar = ActionMainMenuBar1
      end>
    Left = 368
    StyleName = 'Platform Default'
    object Open: TAction
      Caption = 'Open'
      OnExecute = OpenExecute
    end
  end
  object OpenJSON: TOpenDialog
    Filter = '3D scene (*.json)|*.json'
    Left = 448
  end
end
