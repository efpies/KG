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
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Graph: TImage
    Left = 8
    Top = 31
    Width = 703
    Height = 523
    OnMouseDown = GraphMouseDown
    OnMouseMove = GraphMouseMove
    OnMouseUp = GraphMouseUp
  end
  object Label1: TLabel
    Left = 789
    Top = 224
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
    Left = 789
    Top = 271
    Width = 131
    Height = 50
    Caption = #1054#1090#1088#1080#1089#1086#1074#1072#1090#1100
    TabOrder = 1
    OnClick = DrawBtnClick
  end
  object ScaleEdit: TCSpinEdit
    Left = 789
    Top = 243
    Width = 131
    Height = 22
    MaxValue = 100
    MinValue = 1
    TabOrder = 2
  end
  object LabsTabs: TPageControl
    Left = 717
    Top = 31
    Width = 283
    Height = 162
    ActivePage = Lab1
    TabOrder = 3
    OnChange = LabsTabsChange
    object Lab1: TTabSheet
      Caption = '#1'
      object GroupBox1: TGroupBox
        Left = 140
        Top = 3
        Width = 130
        Height = 123
        Caption = #1051#1077#1075#1077#1085#1076#1072
        TabOrder = 0
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
      object Open: TButton
        Left = 3
        Top = 99
        Width = 131
        Height = 25
        Caption = #1054#1090#1082#1088#1099#1090#1100
        TabOrder = 1
        OnClick = OpenClick
      end
      object ReflectionSurfaceSelect: TRadioGroup
        Left = 3
        Top = 3
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
    end
    object Lab2: TTabSheet
      Caption = '#2'
      ImageIndex = 1
      ExplicitLeft = -12
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object Label2: TLabel
        Left = 11
        Top = 11
        Width = 31
        Height = 13
        Caption = #1057#1077#1090#1082#1072
      end
      object Label3: TLabel
        Left = 47
        Top = 33
        Width = 6
        Height = 13
        Caption = 'X'
      end
      object GenerateBezier: TButton
        Left = 151
        Top = 11
        Width = 114
        Height = 120
        Caption = #1057#1075#1077#1085#1077#1088#1080#1088#1086#1074#1072#1090#1100
        TabOrder = 0
        OnClick = GenerateBezierClick
      end
      object BezierRowsField: TEdit
        Left = 11
        Top = 30
        Width = 30
        Height = 21
        NumbersOnly = True
        TabOrder = 1
        Text = '4'
      end
      object BezierColsField: TEdit
        Left = 59
        Top = 30
        Width = 30
        Height = 21
        NumbersOnly = True
        TabOrder = 2
        Text = '4'
      end
      object BezierDetalizationField: TLabeledEdit
        Left = 11
        Top = 72
        Width = 121
        Height = 21
        EditLabel.Width = 135
        EditLabel.Height = 13
        EditLabel.Caption = #1044#1077#1090#1072#1083#1080#1079#1072#1094#1080#1103' '#1087#1086#1074#1077#1088#1093#1085#1086#1089#1090#1080
        TabOrder = 3
        Text = '5'
      end
      object BezierHidePolys: TCheckBox
        Left = 10
        Top = 99
        Width = 135
        Height = 32
        Caption = #1057#1082#1088#1099#1090#1100' '#1087#1086#1083#1080#1075#1086#1085#1072#1083#1100#1085#1091#1102' '#1089#1077#1090#1082#1091
        TabOrder = 4
        WordWrap = True
        OnClick = BezierHidePolysClick
      end
    end
  end
  object ActionManager1: TActionManager
    ActionBars = <
      item
        Items = <
          item
            Action = CloseProgram
          end>
        ActionBar = ActionMainMenuBar1
      end>
    Left = 368
    StyleName = 'Platform Default'
    object CloseProgram: TAction
      Caption = '&'#1042#1099#1093#1086#1076
      OnExecute = CloseProgramExecute
    end
  end
  object OpenJSON: TOpenDialog
    Filter = '3D scene (*.json)|*.json'
    Left = 448
  end
end
