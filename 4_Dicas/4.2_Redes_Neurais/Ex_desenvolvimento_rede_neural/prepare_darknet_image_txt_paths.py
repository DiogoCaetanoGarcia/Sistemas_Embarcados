import os
 
DATA_ROOT_TRAIN = os.path.join(
    '..', 'dataset', 'train'
)
DATA_ROOT_VALID = os.path.join(
    '..', 'dataset', 'valid'
)
 
DATA_ROOT_TEST = os.path.join(
    '..', 'dataset', 'test'
)
 
train_image_files_names = os.listdir(os.path.join(DATA_ROOT_TRAIN))
with open('train.txt', 'w') as f:
    for file_name in train_image_files_names:
        if not '.txt' in file_name:
            write_name = os.path.join(DATA_ROOT_TRAIN, file_name)
            f.writelines(write_name+'\n')
 
valid_data_files__names = os.listdir(os.path.join(DATA_ROOT_VALID))
with open('valid.txt', 'w') as f:
    for file_name in valid_data_files__names:
        if not '.txt' in file_name:
            write_name = os.path.join(DATA_ROOT_VALID, file_name)
            f.writelines(write_name+'\n')
 
test_data_files__names = os.listdir(os.path.join(DATA_ROOT_TEST))
with open('test.txt', 'w') as f:
    for file_name in test_data_files__names:
        if not '.txt' in file_name:
            write_name = os.path.join(DATA_ROOT_TEST, file_name)
            f.writelines(write_name+'\n')