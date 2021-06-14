#define PRESET(...) #__VA_ARGS__

static constexpr char* preset = PRESET(
{
    "input": {
        "gain": 1.0,
        "position": [
            -1290.4296875,
            441.9002380371094
        ]
    },
    "maxBlockSize": 512,
    "nodes": [
        {
            "idx": 0,
            "inputs": [
                [
                    11,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 11,
                    "name": "Bypass",
                    "value": 0.0
                },
                {
                    "idx": 12,
                    "name": "Up",
                    "value": -1.0
                },
                {
                    "idx": 13,
                    "name": "Down",
                    "value": 1.0
                }
            ],
            "position": [
                271.0023193359375,
                446.2724609375
            ],
            "type": "RectifyNode"
        },
        {
            "idx": 1,
            "inputs": [
                [
                    11,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 14,
                    "name": "OverSampling",
                    "value": 1.0
                },
                {
                    "idx": 15,
                    "name": "Bypass",
                    "value": 0.0
                },
                {
                    "idx": 16,
                    "name": "Bass",
                    "value": 0.0
                },
                {
                    "idx": 17,
                    "name": "Drive",
                    "value": 0.4873288571834564
                },
                {
                    "idx": 18,
                    "name": "Offset",
                    "value": 0.0
                },
                {
                    "idx": 19,
                    "name": "Post gain",
                    "value": 0.0
                }
            ],
            "position": [
                344.68670654296875,
                176.79861450195313
            ],
            "type": "SimpleDriveNode"
        },
        {
            "idx": 2,
            "inputs": [
                [
                    1,
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
                    "name": "PAN 1",
                    "value": -1.0
                },
                {
                    "idx": 21,
                    "name": "PAN 2",
                    "value": 1.0
                },
                {
                    "idx": 22,
                    "name": "MIX",
                    "value": 0.7991138100624084
                },
                {
                    "idx": 246,
                    "name": "Add mode",
                    "value": 0.0
                }
            ],
            "position": [
                1433.107177734375,
                168.377685546875
            ],
            "type": "CombineNode"
        },
        {
            "idx": 3,
            "inputs": [
                [
                    0,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 23,
                    "name": "OverSampling",
                    "value": 1.0
                },
                {
                    "idx": 24,
                    "name": "Bypass",
                    "value": 0.0
                },
                {
                    "idx": 25,
                    "name": "Bass",
                    "value": 0.0
                },
                {
                    "idx": 26,
                    "name": "Drive",
                    "value": 0.4873288571834564
                },
                {
                    "idx": 27,
                    "name": "Offset",
                    "value": 0.0
                },
                {
                    "idx": 28,
                    "name": "Post gain",
                    "value": 0.0
                }
            ],
            "position": [
                583.6344604492188,
                409.4305114746094
            ],
            "type": "SimpleDriveNode"
        },
        {
            "idx": 4,
            "inputs": [
                [
                    3,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 0,
                    "name": "Bypass",
                    "value": 0.0
                },
                {
                    "idx": 1,
                    "name": "Up",
                    "value": -1.0
                },
                {
                    "idx": 2,
                    "name": "Down",
                    "value": 1.0
                }
            ],
            "position": [
                768.8970947265625,
                642.0628662109375
            ],
            "type": "RectifyNode"
        },
        {
            "idx": 5,
            "inputs": [
                [
                    4,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 3,
                    "name": "OverSampling",
                    "value": 1.0
                },
                {
                    "idx": 4,
                    "name": "Bypass",
                    "value": 0.0
                },
                {
                    "idx": 5,
                    "name": "Bass",
                    "value": -3.508843421936035
                },
                {
                    "idx": 6,
                    "name": "Drive",
                    "value": 0.0
                },
                {
                    "idx": 7,
                    "name": "Offset",
                    "value": 0.0
                },
                {
                    "idx": 8,
                    "name": "Post gain",
                    "value": 0.0
                }
            ],
            "position": [
                1193.107666015625,
                622.0626220703125
            ],
            "type": "SimpleDriveNode"
        },
        {
            "idx": 6,
            "inputs": [
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
                    "name": "PAN 1",
                    "value": -0.5263174772262573
                },
                {
                    "idx": 10,
                    "name": "PAN 2",
                    "value": 0.7017545700073242
                },
                {
                    "idx": 29,
                    "name": "MIX",
                    "value": 0.42884910106658936
                },
                {
                    "idx": 231,
                    "name": "Add mode",
                    "value": 0.0
                }
            ],
            "position": [
                1243.63427734375,
                381.00921630859375
            ],
            "type": "CombineNode"
        },
        {
            "id": "3ffb0938-41ba-4b7f-8a15-2c0d28dabfed",
            "idx": 7,
            "inputs": [
                [
                    9,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 30,
                    "name": "Bypass",
                    "value": 0.0
                },
                {
                    "idx": 31,
                    "name": "Stereo",
                    "value": 1.0
                }
            ],
            "path": "5d6ed046-903f-4a76-904d-68fa25f91737",
            "position": [
                2258.87841796875,
                -212.92648315429688
            ],
            "type": "CabLibNode"
        },
        {
            "idx": 8,
            "inputs": [
                [
                    12,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 32,
                    "name": "Bypass",
                    "value": 0.0
                },
                {
                    "idx": 33,
                    "name": "Band1",
                    "value": 1000.0
                },
                {
                    "idx": 34,
                    "name": "Band2",
                    "value": 8000.0
                },
                {
                    "idx": 35,
                    "name": "Decay Band1",
                    "value": 0.10090000182390213
                },
                {
                    "idx": 36,
                    "name": "Decay Band2",
                    "value": 0.05298877879977226
                },
                {
                    "idx": 37,
                    "name": "Mix",
                    "value": 0.21005570888519287
                },
                {
                    "idx": 38,
                    "name": "Predelay",
                    "value": 0.0
                }
            ],
            "position": [
                3075.98974609375,
                -97.70437622070313
            ],
            "type": "SimpleReverbNode"
        },
        {
            "idx": 9,
            "inputs": [
                [
                    10,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 39,
                    "name": "OverSampling",
                    "value": 1.0
                },
                {
                    "idx": 40,
                    "name": "Bypass",
                    "value": 0.0
                },
                {
                    "idx": 41,
                    "name": "Bass",
                    "value": 6.584348201751709
                },
                {
                    "idx": 42,
                    "name": "Drive",
                    "value": 0.4423883259296417
                },
                {
                    "idx": 43,
                    "name": "Offset",
                    "value": 0.0
                },
                {
                    "idx": 44,
                    "name": "Post gain",
                    "value": -15.843854904174805
                }
            ],
            "position": [
                1972.9912109375,
                71.1846923828125
            ],
            "type": "SimpleDriveNode"
        },
        {
            "idx": 10,
            "inputs": [
                [
                    2,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 45,
                    "name": "Bypass",
                    "value": 0.0
                },
                {
                    "idx": 46,
                    "name": "Depth",
                    "value": 0.5967096090316772
                },
                {
                    "idx": 47,
                    "name": "Speed",
                    "value": 0.629219114780426
                }
            ],
            "position": [
                1725.21337890625,
                113.4068603515625
            ],
            "type": "PowerSagNode"
        },
        {
            "idx": 11,
            "inputs": [
                [
                    -1,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 48,
                    "name": "Bypass",
                    "value": 0.0
                },
                {
                    "idx": 49,
                    "name": "Attack",
                    "value": 0.009999999776482582
                },
                {
                    "idx": 50,
                    "name": "Hold",
                    "value": 0.10000000149011612
                },
                {
                    "idx": 51,
                    "name": "Release",
                    "value": 0.10000000149011612
                },
                {
                    "idx": 52,
                    "name": "Threshold",
                    "value": -57.03684616088867
                }
            ],
            "position": [
                -888.1783447265625,
                411.6526794433594
            ],
            "type": "SimpleGateNode"
        },
        {
            "idx": 12,
            "inputs": [
                [
                    14,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 53,
                    "name": "Bypass",
                    "value": 1.0
                },
                {
                    "idx": 54,
                    "name": "Left",
                    "value": 1.0
                },
                {
                    "idx": 55,
                    "name": "Left/Right Offset",
                    "value": 0.22633756697177887
                },
                {
                    "idx": 56,
                    "name": "Phase Fine",
                    "value": 0.0
                },
                {
                    "idx": 57,
                    "name": "Phase Rough",
                    "value": 0.0
                },
                {
                    "idx": 58,
                    "name": "Right",
                    "value": 1.0
                }
            ],
            "position": [
                2775.21484375,
                -164.92660522460938
            ],
            "type": "PhaseToolNode"
        },
        {
            "id": "38ea6b10-1dd0-4282-b998-4d89e87ccd32",
            "idx": 13,
            "inputs": [
                [
                    9,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 59,
                    "name": "Bypass",
                    "value": 0.0
                },
                {
                    "idx": 60,
                    "name": "Stereo",
                    "value": 1.0
                }
            ],
            "path": "6ed4183e-93e5-4bf7-9945-00a5cdfb8e60",
            "position": [
                2264.87841796875,
                97.0736083984375
            ],
            "type": "CabLibNode"
        },
        {
            "idx": 14,
            "inputs": [
                [
                    7,
                    0
                ],
                [
                    13,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 61,
                    "name": "PAN 1",
                    "value": 0.20370087027549744
                },
                {
                    "idx": 62,
                    "name": "PAN 2",
                    "value": -0.14814814925193787
                },
                {
                    "idx": 63,
                    "name": "MIX",
                    "value": 0.742222249507904
                },
                {
                    "idx": 204,
                    "name": "Add mode",
                    "value": 0.0
                }
            ],
            "position": [
                2477.8779296875,
                -92.92654418945313
            ],
            "type": "CombineNode"
        },
        {
            "idx": 15,
            "inputs": [
                [
                    8,
                    0
                ]
            ],
            "parameters": [
                {
                    "idx": 64,
                    "name": "Bypass",
                    "value": 0.0
                },
                {
                    "idx": 65,
                    "name": "Gain",
                    "value": 10.400002479553223
                }
            ],
            "position": [
                3395.1064453125,
                -136.38613891601563
            ],
            "type": "AutoGainNode"
        }
    ],
    "output": {
        "gain": 1.0,
        "inputs": [
            [
                15,
                0
            ]
        ],
        "position": [
            3737.8291015625,
            -164.78103637695313
        ]
    },
    "version": "PLUG_VERSION_HEX"
}
);