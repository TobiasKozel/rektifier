#define PRESET(...) #__VA_ARGS__

static constexpr char* preset = PRESET(
  {
    "input": {
        "gain": 1.0,
        "position" : [
            -1883.4296875,
            529.9002685546875
        ]
    },
    "maxBlockSize": 512,
    "nodes" : [
        {
            "idx": 0,
            "inputs" : [
                [
                    13,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 11,
                    "name" : "Bypass",
                    "value" : 0.0
                },
                {
                    "idx": 12,
                    "name" : "Up",
                    "value" : -1.0
                },
                {
                    "idx": 13,
                    "name" : "Down",
                    "value" : 1.0
                }
            ],
            "position": [
                -321.99755859375,
                534.2724609375
            ] ,
            "type" : "RectifyNode"
        },
        {
            "idx": 1,
            "inputs" : [
                [
                    13,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 14,
                    "name" : "OverSampling",
                    "value" : 1.0
                },
                {
                    "idx": 15,
                    "name" : "Bypass",
                    "value" : 0.0
                },
                {
                    "idx": 16,
                    "name" : "Bass",
                    "value" : 0.0
                },
                {
                    "idx": 17,
                    "name" : "Drive",
                    "value" : 0.4873288571834564
                },
                {
                    "idx": 18,
                    "name" : "Offset",
                    "value" : 0.0
                },
                {
                    "idx": 19,
                    "name" : "Post gain",
                    "value" : 0.0
                }
            ],
            "position": [
                -304.313232421875,
                28.798583984375
            ] ,
            "type" : "SimpleDriveNode"
        },
        {
            "idx": 2,
            "inputs" : [
                [
                    17,
                    0
                ],
                [
                    6,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 20,
                    "name" : "PAN 1",
                    "value" : 0.0
                },
                {
                    "idx": 21,
                    "name" : "PAN 2",
                    "value" : 1.0
                },
                {
                    "idx": 22,
                    "name" : "MIX",
                    "value" : 0.0
                },
                {
                    "idx": 246,
                    "name" : "Add mode",
                    "value" : 0.0
                }
            ],
            "position": [
                790.107177734375,
                215.377685546875
            ] ,
            "type" : "CombineNode"
        },
        {
            "idx": 3,
            "inputs" : [
                [
                    0,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 23,
                    "name" : "OverSampling",
                    "value" : 1.0
                },
                {
                    "idx": 24,
                    "name" : "Bypass",
                    "value" : 0.0
                },
                {
                    "idx": 25,
                    "name" : "Bass",
                    "value" : 0.0
                },
                {
                    "idx": 26,
                    "name" : "Drive",
                    "value" : 0.4873288571834564
                },
                {
                    "idx": 27,
                    "name" : "Offset",
                    "value" : 0.0
                },
                {
                    "idx": 28,
                    "name" : "Post gain",
                    "value" : 0.0
                }
            ],
            "position": [
                -9.365478515625,
                497.4305419921875
            ] ,
            "type" : "SimpleDriveNode"
        },
        {
            "idx": 4,
            "inputs" : [
                [
                    3,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 0,
                    "name" : "Bypass",
                    "value" : 0.0
                },
                {
                    "idx": 1,
                    "name" : "Up",
                    "value" : -1.0
                },
                {
                    "idx": 2,
                    "name" : "Down",
                    "value" : 1.0
                }
            ],
            "position": [
                175.89697265625,
                730.0628662109375
            ] ,
            "type" : "RectifyNode"
        },
        {
            "idx": 5,
            "inputs" : [
                [
                    4,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 3,
                    "name" : "OverSampling",
                    "value" : 1.0
                },
                {
                    "idx": 4,
                    "name" : "Bypass",
                    "value" : 0.0
                },
                {
                    "idx": 5,
                    "name" : "Bass",
                    "value" : -3.508843421936035
                },
                {
                    "idx": 6,
                    "name" : "Drive",
                    "value" : 0.0
                },
                {
                    "idx": 7,
                    "name" : "Offset",
                    "value" : 0.0
                },
                {
                    "idx": 8,
                    "name" : "Post gain",
                    "value" : 0.0
                }
            ],
            "position": [
                600.107666015625,
                710.0626220703125
            ] ,
            "type" : "SimpleDriveNode"
        },
        {
            "idx": 6,
            "inputs" : [
                [
                    3,
                    0
                ],
                [
                    5,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 9,
                    "name" : "PAN 1",
                    "value" : -0.5263174772262573
                },
                {
                    "idx": 10,
                    "name" : "PAN 2",
                    "value" : 0.7017545700073242
                },
                {
                    "idx": 29,
                    "name" : "MIX",
                    "value" : 0.42884910106658936
                },
                {
                    "idx": 231,
                    "name" : "Add mode",
                    "value" : 0.0
                }
            ],
            "position": [
                650.63427734375,
                469.00921630859375
            ] ,
            "type" : "CombineNode"
        },
        {
            "id": "3ffb0938-41ba-4b7f-8a15-2c0d28dabfed",
            "idx" : 7,
            "inputs" : [
                [
                    8,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 30,
                    "name" : "Bypass",
                    "value" : 0.0
                },
                {
                    "idx": 31,
                    "name" : "Stereo",
                    "value" : 1.0
                }
            ],
            "path": "5d6ed046-903f-4a76-904d-68fa25f91737",
            "position" : [
                1665.87841796875,
                -124.92648315429688
            ] ,
            "type" : "CabLibNode"
        },
        {
            "idx": 8,
            "inputs" : [
                [
                    9,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 39,
                    "name" : "OverSampling",
                    "value" : 1.0
                },
                {
                    "idx": 40,
                    "name" : "Bypass",
                    "value" : 0.0
                },
                {
                    "idx": 41,
                    "name" : "Bass",
                    "value" : 6.584348201751709
                },
                {
                    "idx": 42,
                    "name" : "Drive",
                    "value" : 0.4423883259296417
                },
                {
                    "idx": 43,
                    "name" : "Offset",
                    "value" : 0.0
                },
                {
                    "idx": 44,
                    "name" : "Post gain",
                    "value" : -15.843854904174805
                }
            ],
            "position": [
                1379.9912109375,
                159.1846923828125
            ] ,
            "type" : "SimpleDriveNode"
        },
        {
            "idx": 9,
            "inputs" : [
                [
                    18,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 45,
                    "name" : "Bypass",
                    "value" : 0.0
                },
                {
                    "idx": 46,
                    "name" : "Depth",
                    "value" : 0.5967096090316772
                },
                {
                    "idx": 47,
                    "name" : "Speed",
                    "value" : 0.629219114780426
                }
            ],
            "position": [
                1172.21337890625,
                11.4068603515625
            ] ,
            "type" : "PowerSagNode"
        },
        {
            "idx": 10,
            "inputs" : [
                [
                    -1,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 48,
                    "name" : "Bypass",
                    "value" : 0.0
                },
                {
                    "idx": 49,
                    "name" : "Attack",
                    "value" : 0.009999999776482582
                },
                {
                    "idx": 50,
                    "name" : "Hold",
                    "value" : 0.10000000149011612
                },
                {
                    "idx": 51,
                    "name" : "Release",
                    "value" : 0.10000000149011612
                },
                {
                    "idx": 52,
                    "name" : "Threshold",
                    "value" : -57.03684616088867
                }
            ],
            "position": [
                -1481.17822265625,
                499.6527099609375
            ] ,
            "type" : "SimpleGateNode"
        },
        {
            "id": "38ea6b10-1dd0-4282-b998-4d89e87ccd32",
            "idx" : 11,
            "inputs" : [
                [
                    8,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 59,
                    "name" : "Bypass",
                    "value" : 0.0
                },
                {
                    "idx": 60,
                    "name" : "Stereo",
                    "value" : 1.0
                }
            ],
            "path": "6ed4183e-93e5-4bf7-9945-00a5cdfb8e60",
            "position" : [
                1691.87841796875,
                269.0736083984375
            ] ,
            "type" : "CabLibNode"
        },
        {
            "idx": 12,
            "inputs" : [
                [
                    7,
                    0
                ],
                [
                    11,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 61,
                    "name" : "PAN 1",
                    "value" : 0.20370087027549744
                },
                {
                    "idx": 62,
                    "name" : "PAN 2",
                    "value" : -0.14814814925193787
                },
                {
                    "idx": 63,
                    "name" : "MIX",
                    "value" : 0.742222249507904
                },
                {
                    "idx": 204,
                    "name" : "Add mode",
                    "value" : 0.0
                }
            ],
            "position": [
                2071.8779296875,
                -4.926544189453125
            ] ,
            "type" : "CombineNode"
        },
        {
            "idx": 13,
            "inputs" : [
                [
                    10,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 32,
                    "name" : "Bypass",
                    "value" : 0.0
                },
                {
                    "idx": 33,
                    "name" : "Gain",
                    "value" : 0.0
                }
            ],
            "position": [
                -987.0,
                476.0
            ] ,
            "type" : "AutoGainNode"
        },
        {
            "idx": 14,
            "inputs" : [
                [
                    15,
                    0
                ],
                [
                    12,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 34,
                    "name" : "PAN 1",
                    "value" : 0.0
                },
                {
                    "idx": 35,
                    "name" : "PAN 2",
                    "value" : 0.0
                },
                {
                    "idx": 36,
                    "name" : "MIX",
                    "value" : 1.0
                },
                {
                    "idx": 211,
                    "name" : "Add mode",
                    "value" : 0.0
                }
            ],
            "position": [
                2400.0,
                109.0
            ] ,
            "type" : "CombineNode"
        },
        {
            "idx": 15,
            "inputs" : [
                [
                    8,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 37,
                    "name" : "Bypass",
                    "value" : 0.0
                },
                {
                    "idx": 38,
                    "name" : "Left",
                    "value" : 1.0
                },
                {
                    "idx": 53,
                    "name" : "Left/Right Offset",
                    "value" : 0.0
                },
                {
                    "idx": 54,
                    "name" : "Phase Fine",
                    "value" : 9.259259240934625e-05
                },
                {
                    "idx": 55,
                    "name" : "Phase Rough",
                    "value" : 0.0
                },
                {
                    "idx": 56,
                    "name" : "Right",
                    "value" : 1.0
                }
            ],
            "position": [
                2106.0,
                197.0
            ] ,
            "type" : "PhaseToolNode"
        },
        {
            "idx": 16,
            "inputs" : [
                [
                    13,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 57,
                    "name" : "OverSampling",
                    "value" : 1.0
                },
                {
                    "idx": 58,
                    "name" : "Bypass",
                    "value" : 0.0
                },
                {
                    "idx": 64,
                    "name" : "Bass",
                    "value" : -5.185185432434082
                },
                {
                    "idx": 65,
                    "name" : "Drive",
                    "value" : 0.8021436929702759
                },
                {
                    "idx": 66,
                    "name" : "Offset",
                    "value" : 0.032592594623565674
                },
                {
                    "idx": 67,
                    "name" : "Post gain",
                    "value" : -8.799997329711914
                }
            ],
            "position": [
                -298.313232421875,
                268.798583984375
            ] ,
            "type" : "SimpleDriveNode"
        },
        {
            "idx": 17,
            "inputs" : [
                [
                    1,
                    0
                ],
                [
                    16,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 68,
                    "name" : "PAN 1",
                    "value" : -1.0
                },
                {
                    "idx": 69,
                    "name" : "PAN 2",
                    "value" : 1.0
                },
                {
                    "idx": 70,
                    "name" : "MIX",
                    "value" : 0.5
                },
                {
                    "idx": 198,
                    "name" : "Add mode",
                    "value" : 1.0
                }
            ],
            "position": [
                286.107177734375,
                194.377685546875
            ] ,
            "type" : "CombineNode"
        },
        {
            "idx": 18,
            "inputs" : [
                [
                    2,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 71,
                    "name" : "Bypass",
                    "value" : 0.0
                },
                {
                    "idx": 72,
                    "name" : "Panning",
                    "value" : 0.0
                },
                {
                    "idx": 73,
                    "name" : "Post panning",
                    "value" : 0.0
                },
                {
                    "idx": 74,
                    "name" : "Width",
                    "value" : 1.0
                }
            ],
            "position": [
                1083.0,
                234.0
            ] ,
            "type" : "StereoToolNode"
        }
    ],
    "output": {
        "gain": 1.0,
        "inputs" : [
            [
                14,
                0
            ]
        ],
        "position": [
            3144.8291015625,
            -76.78103637695313
        ]
    },
    "version": "PLUG_VERSION_HEX"
  }
);