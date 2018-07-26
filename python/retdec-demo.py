from retdec.decompiler import Decompiler

decompiler = Decompiler(api_key='7dd6cdea-e697-46fe-bff1-416cea11595b')
decompilation = decompiler.start_decompilation(input_file='babymips')
decompilation.wait_until_finished()
decompilation.save_hll_code()