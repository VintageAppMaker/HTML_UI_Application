object frmMainView: TfrmMainView
  Left = 480
  Top = 197
  BorderStyle = bsSingle
  Caption = 'Game Browser'
  ClientHeight = 478
  ClientWidth = 527
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = mmMain
  OldCreateOrder = False
  Position = poDesigned
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 527
    Height = 478
    Align = alClient
    TabOrder = 0
    ExplicitWidth = 577
    ExplicitHeight = 488
    object wbMainView: TWebBrowser
      Left = 1
      Top = 1
      Width = 525
      Height = 476
      Align = alClient
      TabOrder = 0
      OnBeforeNavigate2 = wbMainViewBeforeNavigate2
      OnDocumentComplete = wbMainViewDocumentComplete
      ExplicitLeft = 54
      ExplicitWidth = 404
      ExplicitHeight = 413
      ControlData = {
        4C00000043360000323100000000000000000000000000000000000000000000
        000000004C000000000000000000000001000000E0D057007335CF11AE690800
        2B2E12620A000000000000004C0000000114020000000000C000000000000046
        8000000000000000000000000000000000000000000000000000000000000000
        00000000000000000100000000000000000000000000000000000000}
    end
  end
  object mmMain: TMainMenu
    Left = 736
    Top = 408
    object fiel1: TMenuItem
      Caption = #54028#51068
      object N1: TMenuItem
        Caption = #47700#51064#54868#47732
        OnClick = N1Click
      end
      object N2: TMenuItem
        Caption = #50976#51200#51221#48372
        OnClick = N2Click
      end
    end
    object N3: TMenuItem
      Caption = #46020#50880#47568
      object about1: TMenuItem
        Caption = 'about'
        OnClick = about1Click
      end
    end
  end
end
