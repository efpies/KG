object MainForm: TMainForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = #1051#1072#1073#1086#1088#1072#1090#1086#1088#1085#1072#1103' '#1088#1072#1073#1086#1090#1072' '#8470'1 | '#1071#1089#1085#1086#1074' '#1053#1080#1082#1086#1083#1072#1081' '#1075#1088'. 8306'
  ClientHeight = 582
  ClientWidth = 1028
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  Scaled = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Graph: TImage
    Left = 8
    Top = 31
    Width = 723
    Height = 543
    OnMouseDown = GraphMouseDown
    OnMouseMove = GraphMouseMove
    OnMouseUp = GraphMouseUp
  end
  object Label1: TLabel
    Left = 567
    Top = 445
    Width = 45
    Height = 13
    Caption = #1052#1072#1089#1096#1090#1072#1073
  end
  object ActionMainMenuBar1: TActionMainMenuBar
    Left = 0
    Top = 0
    Width = 1028
    Height = 25
    UseSystemFont = False
    ActionManager = ActionMgr
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
    ExplicitWidth = 1008
  end
  object DrawBtn: TButton
    Left = 567
    Top = 492
    Width = 131
    Height = 50
    Caption = #1054#1090#1088#1080#1089#1086#1074#1072#1090#1100
    TabOrder = 0
    OnClick = DrawBtnClick
  end
  object ScaleEdit: TCSpinEdit
    Left = 567
    Top = 464
    Width = 131
    Height = 22
    MaxValue = 100
    MinValue = 1
    TabOrder = 1
  end
  object LabsTabs: TPageControl
    Left = 737
    Top = 31
    Width = 283
    Height = 543
    ActivePage = Lab4
    MultiLine = True
    TabOrder = 2
    OnChange = LabsTabsChange
    object Lab1: TTabSheet
      Caption = '#1'
      ExplicitHeight = 412
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
      ExplicitHeight = 412
      object Label2: TLabel
        Left = 11
        Top = 3
        Width = 31
        Height = 13
        Caption = #1057#1077#1090#1082#1072
      end
      object Label3: TLabel
        Left = 47
        Top = 26
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
        Top = 22
        Width = 30
        Height = 21
        NumbersOnly = True
        TabOrder = 1
        Text = '4'
      end
      object BezierColsField: TEdit
        Left = 59
        Top = 22
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
        Checked = True
        State = cbChecked
        TabOrder = 4
        WordWrap = True
        OnClick = BezierHidePolysClick
      end
    end
    object Lab3: TTabSheet
      Caption = '#3'
      ImageIndex = 2
      ExplicitHeight = 412
      object DrawStyleRadioGroup: TRadioGroup
        Left = 3
        Top = 3
        Width = 102
        Height = 54
        Caption = #1057#1090#1080#1083#1100' '#1086#1090#1088#1080#1089#1086#1074#1082#1080
        ItemIndex = 1
        Items.Strings = (
          #1057#1077#1090#1082#1072
          #1047#1072#1083#1080#1074#1082#1072)
        TabOrder = 0
        OnClick = DrawStyleRadioGroupClick
      end
      object GroupBox2: TGroupBox
        Left = 111
        Top = 3
        Width = 159
        Height = 87
        Caption = #1062#1074#1077#1090' '#1079#1072#1083#1080#1074#1082#1080
        TabOrder = 1
        object FrontColorPicker: TImage
          Left = 23
          Top = 34
          Width = 43
          Height = 43
          OnClick = FrontColorPickerClick
        end
        object BackColorPicker: TImage
          Left = 100
          Top = 34
          Width = 43
          Height = 43
          OnClick = BackColorPickerClick
        end
        object Label6: TLabel
          Left = 10
          Top = 15
          Width = 68
          Height = 13
          Caption = #1060#1088#1086#1085#1090#1072#1083#1100#1085#1072#1103
        end
        object Label7: TLabel
          Left = 96
          Top = 15
          Width = 50
          Height = 13
          Caption = #1054#1073#1088#1072#1090#1085#1072#1103
        end
      end
    end
    object Lab4: TTabSheet
      Caption = '#4'
      ImageIndex = 3
      ExplicitHeight = 412
      object GroupBox3: TGroupBox
        Left = 5
        Top = 3
        Width = 267
        Height = 509
        Caption = #1054#1089#1074#1077#1097#1077#1085#1080#1077
        TabOrder = 0
        object GroupBoxSourceLight: TGroupBox
          Left = 10
          Top = 15
          Width = 247
          Height = 115
          Caption = #1048#1089#1090#1086#1095#1085#1080#1082' '#1089#1074#1077#1090#1072
          TabOrder = 0
          object Label8: TLabel
            Left = 37
            Top = 23
            Width = 25
            Height = 13
            Caption = #1057#1074#1077#1090
          end
          object SourceLightColorPicker: TImage
            Left = 28
            Top = 42
            Width = 43
            Height = 43
            OnClick = SourceLightColorPickerClick
          end
          object GroupBox4: TGroupBox
            Left = 99
            Top = 10
            Width = 137
            Height = 95
            Caption = #1055#1086#1083#1086#1078#1077#1085#1080#1077' '#1080#1089#1090#1086#1095#1085#1080#1082#1072
            TabOrder = 0
            object Label11: TLabel
              Left = 16
              Top = 45
              Width = 6
              Height = 13
              Caption = 'Y'
            end
            object Label12: TLabel
              Left = 16
              Top = 67
              Width = 6
              Height = 13
              Caption = 'Z'
            end
            object Label9: TLabel
              Left = 16
              Top = 22
              Width = 6
              Height = 13
              Caption = 'X'
            end
            object SourcePosXTextField: TEdit
              Left = 28
              Top = 18
              Width = 43
              Height = 21
              Ctl3D = True
              ParentCtl3D = False
              TabOrder = 0
              Text = '0'
            end
            object SourcePosYTextField: TEdit
              Left = 28
              Top = 42
              Width = 43
              Height = 21
              Ctl3D = True
              ParentCtl3D = False
              TabOrder = 1
              Text = '0'
            end
            object SourcePosZTextField: TEdit
              Left = 28
              Top = 65
              Width = 43
              Height = 21
              Ctl3D = True
              ParentCtl3D = False
              TabOrder = 2
              Text = '50'
            end
            object SourcePosXIncrementButton: TButton
              Left = 77
              Top = 18
              Width = 21
              Height = 21
              Caption = '+'
              TabOrder = 3
              OnClick = SourcePosXIncrementButtonClick
            end
            object SourcePosXDecrementButton: TButton
              Left = 102
              Top = 18
              Width = 21
              Height = 21
              Caption = #8212
              TabOrder = 4
              OnClick = SourcePosXDecrementButtonClick
            end
            object SourcePosYDecrementButton: TButton
              Left = 102
              Top = 42
              Width = 21
              Height = 21
              Caption = #8212
              TabOrder = 5
              OnClick = SourcePosYDecrementButtonClick
            end
            object SourcePosYIncrementButton: TButton
              Left = 77
              Top = 42
              Width = 21
              Height = 21
              Caption = '+'
              TabOrder = 6
              OnClick = SourcePosYIncrementButtonClick
            end
            object SourcePosZIncrementButton: TButton
              Left = 77
              Top = 65
              Width = 21
              Height = 21
              Caption = '+'
              TabOrder = 7
              OnClick = SourcePosZIncrementButtonClick
            end
            object SourcePosZDecrementButton: TButton
              Left = 102
              Top = 65
              Width = 21
              Height = 21
              Caption = #8212
              TabOrder = 8
              OnClick = SourcePosZDecrementButtonClick
            end
          end
        end
        object GroupBoxAmbientLight: TGroupBox
          Left = 10
          Top = 136
          Width = 247
          Height = 113
          Caption = #1060#1086#1085#1086#1074#1086#1077' '#1086#1089#1074#1077#1097#1077#1085#1080#1077
          TabOrder = 1
          object AmbientLightColorPicker: TImage
            Left = 28
            Top = 58
            Width = 43
            Height = 43
            OnClick = AmbientLightColorPickerClick
          end
          object Label13: TLabel
            Left = 37
            Top = 39
            Width = 25
            Height = 13
            Caption = #1057#1074#1077#1090
          end
          object Label14: TLabel
            Left = 110
            Top = 39
            Width = 77
            Height = 13
            Caption = #1048#1085#1090#1077#1085#1089#1080#1074#1085#1086#1089#1090#1100
          end
          object AmbientLightIntensityTrackBar: TTrackBar
            Left = 99
            Top = 57
            Width = 137
            Height = 45
            Ctl3D = True
            LineSize = 10
            Max = 100
            ParentCtl3D = False
            PageSize = 25
            ShowSelRange = False
            TabOrder = 0
            ThumbLength = 40
            TickMarks = tmBoth
            TickStyle = tsNone
            OnChange = AmbientLightIntensityTrackBarChange
          end
          object UseAmbientLightModelCheckBox: TCheckBox
            Left = 14
            Top = 15
            Width = 97
            Height = 17
            Caption = #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100
            Checked = True
            State = cbChecked
            TabOrder = 1
            OnClick = UseAmbientLightModelCheckBoxClick
          end
        end
        object GroupBoxDiffusionLigth: TGroupBox
          Left = 10
          Top = 255
          Width = 247
          Height = 82
          Caption = #1044#1080#1092#1092#1091#1079#1085#1086#1077' '#1086#1089#1074#1077#1097#1077#1085#1080#1077
          TabOrder = 2
          object Label15: TLabel
            Left = 11
            Top = 38
            Width = 182
            Height = 13
            Caption = #1050#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090' '#1076#1080#1092#1092#1091#1079#1080#1080' '#1084#1072#1090#1077#1088#1080#1072#1083#1072
          end
          object DiffusionCoeffTrackBar: TTrackBar
            Left = 3
            Top = 57
            Width = 241
            Height = 20
            Ctl3D = True
            LineSize = 10
            Max = 100
            ParentCtl3D = False
            PageSize = 25
            Position = 75
            ShowSelRange = False
            TabOrder = 0
            ThumbLength = 15
            TickMarks = tmBoth
            TickStyle = tsNone
            OnChange = AmbientLightIntensityTrackBarChange
          end
          object UseDiffusionLightModelCheckBox: TCheckBox
            Left = 14
            Top = 15
            Width = 97
            Height = 17
            Caption = #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100
            Checked = True
            State = cbChecked
            TabOrder = 1
            OnClick = UseDiffusionLightModelCheckBoxClick
          end
        end
        object GroupBoxReflectionLight: TGroupBox
          Left = 10
          Top = 343
          Width = 247
          Height = 82
          Caption = #1047#1077#1088#1082#1072#1083#1100#1085#1086#1077' '#1086#1089#1074#1077#1097#1077#1085#1080#1077
          TabOrder = 3
          object Label16: TLabel
            Left = 11
            Top = 38
            Width = 182
            Height = 13
            Caption = #1050#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090' '#1076#1080#1092#1092#1091#1079#1080#1080' '#1084#1072#1090#1077#1088#1080#1072#1083#1072
          end
          object TrackBar1: TTrackBar
            Left = 3
            Top = 57
            Width = 241
            Height = 20
            Ctl3D = True
            LineSize = 10
            Max = 100
            ParentCtl3D = False
            PageSize = 25
            Position = 75
            ShowSelRange = False
            TabOrder = 0
            ThumbLength = 15
            TickMarks = tmBoth
            TickStyle = tsNone
            OnChange = AmbientLightIntensityTrackBarChange
          end
          object UseReflectionLightModelCheckBox: TCheckBox
            Left = 14
            Top = 15
            Width = 97
            Height = 17
            Caption = #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100
            Checked = True
            State = cbChecked
            TabOrder = 1
            OnClick = UseReflectionLightModelCheckBoxClick
          end
        end
      end
    end
  end
  object ActionMgr: TActionManager
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
  object PickColor: TColorDialog
    Left = 504
  end
end
