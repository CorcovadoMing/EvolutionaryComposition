from pydub import AudioSegment

sound1 = AudioSegment.from_file("1.wav")
sound2 = AudioSegment.from_file("./handler/background.wav")

combined = sound1.overlay(sound2)
combined.export("result1.wav", format='wav')

sound1 = AudioSegment.from_file("2.wav")
sound2 = AudioSegment.from_file("./handler/background.wav")

combined = sound1.overlay(sound2)
combined.export("result2.wav", format='wav')

sound1 = AudioSegment.from_file("3.wav")
sound2 = AudioSegment.from_file("./handler/background.wav")

combined = sound1.overlay(sound2)
combined.export("result3.wav", format='wav')

sound1 = AudioSegment.from_file("4.wav")
sound2 = AudioSegment.from_file("./handler/background.wav")

combined = sound1.overlay(sound2)
combined.export("result4.wav", format='wav')