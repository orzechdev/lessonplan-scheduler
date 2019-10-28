def is_data_valid(classes_subjects, teachers_subjects, rooms_subjects):
    for class_subjects in classes_subjects:
        for class_subject in class_subjects:
            is_teacher_available = False
            is_room_available = False
            for teacher_subjects in teachers_subjects:
                for teacher_subject in teacher_subjects:
                    if teacher_subject == class_subject:
                        is_teacher_available = True
                        break
                if is_teacher_available:
                    break
            if not is_teacher_available:
                return False, "at least one teacher for class subject is unavailable"
            for room_subjects in rooms_subjects:
                if len(room_subjects) == 0:
                    is_room_available = True
                for room_subject in room_subjects:
                    if room_subject == class_subject:
                        is_room_available = False
                        break
                if is_room_available:
                    break
            if not is_room_available:
                return False, "at least one room for class subject is unavailable"
    return True, None
